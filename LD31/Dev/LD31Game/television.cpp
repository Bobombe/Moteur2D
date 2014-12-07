#include "television.h"
#include <fstream>
#include <iostream>
#include "moteur2d.h"
#include "personnage.h"

#define Epaisseur_Bords 300

void Television::init()
{
    for (int i = 0; i< m_secteurs.size(); i++)
    {
        m_secteurs.at(i).init();
    }
    for (int i = 0; i< m_connecteurs.size(); i++)
    {
        m_connecteurs.at(i).etteindre();
    }
    m_score=0;
}

Television::Television(std::string nom) : m_window(Moteur2D::getInstance()->getWindow())
{
    m_secteurPerso = 2;
    //ctor
    /*/ On charge les textures de couleur
    m_gris=Moteur2D::getInstance()->getTexture("ressources\\Fonds\\Gris.png");
    m_gris->setRepeated(true);//*/

    // On charge les param de l'écran
    std::ifstream file(("ressources\\"+nom+"\\"+nom+".txt").c_str(), std::ios::in);
    std::string skip;
    getline(file, skip);
    file>>m_size.x;
    file>>m_size.y;

    // Bord Bas
    m_obstaclesPermanents.push_back(Obstacle("Gris", m_size.x+2*Epaisseur_Bords, Epaisseur_Bords, -Epaisseur_Bords, m_size.y));

    // Bord Haut
    m_obstaclesPermanents.push_back(Obstacle("Gris", m_size.x+2*Epaisseur_Bords, Epaisseur_Bords, -Epaisseur_Bords, -Epaisseur_Bords));

    // Bord Gauche
    m_obstaclesPermanents.push_back(Obstacle("Gris", Epaisseur_Bords, m_size.y+2*Epaisseur_Bords, -Epaisseur_Bords, -Epaisseur_Bords));

    // Bord Gauche
    m_obstaclesPermanents.push_back(Obstacle("Gris", Epaisseur_Bords, m_size.y+2*Epaisseur_Bords, m_size.x, -Epaisseur_Bords));

    //Preparation des secteurs
    int tailleSecteur = 250;// secteurs carrés
    m_nbColones = m_size.x/tailleSecteur;
    m_nbLignes = m_size.x/tailleSecteur;
    //
    for (int i = 0; i<m_nbLignes; i++)
    {
        for (int j = 0; j<m_nbColones; j++)
        {
            m_secteurs.push_back(Secteur(j*250, i*250));
        }

    }

    // 2 lignes de commentaires
    getline(file, skip);
    getline(file, skip);


    // Lecture des obstacles
    int couleur, px, py;
    while (getline(file, skip))
    {
        file>>couleur;
        file>>px;
        file>>py;


        int coloneObs = px/250;
        int secteurObs = py/250;
        secteurObs*=m_nbLignes;
        secteurObs+=coloneObs;
        if(couleur >20)
        {
            m_flammes.push_back(Flamme(couleur-20, px, py));
        }
        else if(couleur >10)
        {
            m_connecteurs.push_back(Connecteur(couleur-10, px, py));
        }
        else
        {
            m_secteurs.at(secteurObs).addObstacle(couleur, 10, 10, px, py);
        }


    }//*/

    // Suivi de progression
    m_score = 0;
    m_conteneur.setTexture(*Moteur2D::getInstance()->getTexture("ressources\\Conteneur.png"));
    m_charge.setTexture(*Moteur2D::getInstance()->getTexture("ressources\\Fonds\\Blanc.png", true));
    m_fin.setTexture(*Moteur2D::getInstance()->getTexture("ressources\\Fin.png"));

    Moteur2D::getInstance()->addPostUpdate(this);

}

Television::~Television()
{
    //dtor
}

void Television::update(float seconds)
{
    for (unsigned int i = 0; i<m_obstaclesPermanents.size(); i++)
    {
        m_window.draw(m_obstaclesPermanents.at(i).m_sprite);
    }

    // Dessine les Secteurs

    for (unsigned int i = 0; i<m_secteurs.size(); i++)
    {
        m_secteurs.at(i).draw(m_window);
    }

    // Dessine les Connecteurs

    for (unsigned int i = 0; i<m_connecteurs.size(); i++)
    {
        m_window.draw(m_connecteurs.at(i).m_sprite);
    }

    // Dessine les Flammes

    for (unsigned int i = 0; i<m_flammes.size(); i++)
    {
        m_window.draw(m_flammes.at(i).m_sprite);
    }

    // Dessine la progression, fixe !
    sf::Vector2f c = Moteur2D::getInstance()->getView()->getCenter();
    m_conteneur.setPosition(c.x+512-210-40, c.y-384+40);
    m_charge.setPosition(c.x+512-210-40+10, c.y-384+40+10);
    m_fin.setPosition(c.x-512+119, c.y-384+298);
    int tx = m_connecteurs.size();
    if(tx>0&&m_score>=0)
    {
        tx =m_score*190/m_connecteurs.size();
    }
    else
    {
        tx = 190;
    }
    m_charge.setTextureRect(sf::IntRect(0, 0, tx, 20));
    m_window.draw(m_conteneur);
    m_window.draw(m_charge);
    if(m_score>=m_connecteurs.size())
    {
        m_window.draw(m_fin);
    }


}

void Television::collisionPersonnage(Personnage * perso, sf::Vector2f oldPos)
{
    // Collision avec les obstacles permanents
    for (unsigned int i = 0; i<m_obstaclesPermanents.size(); i++)
    {
        collisionEntre(perso, oldPos, m_obstaclesPermanents.at(i));
    }

    // Collision avec les objets des secteurs
    for (int i =m_secteurPerso-m_nbColones-1; i<=m_secteurPerso-m_nbColones+1; i++)
    {
        if(i>=0 && i< m_nbColones*m_nbLignes)
        {
            std::vector<Obstacle> obss =m_secteurs.at(i).getCollidables(perso->getTorche(), perso->getPosition());
            for (unsigned int j = 0; j<obss.size(); j++)
            {
                collisionEntre(perso, oldPos, obss.at(j));
            }
        }
    }
    for (int i =m_secteurPerso-1; i<=m_secteurPerso+1; i++)
    {
        if(i>=0 && i< m_nbColones*m_nbLignes)
        {
            std::vector<Obstacle> obss= m_secteurs.at(i).getCollidables(perso->getTorche(), perso->getPosition());
            for (unsigned int j = 0; j<obss.size(); j++)
            {
                collisionEntre(perso, oldPos, obss.at(j));
            }
        }
    }
    for (int i =m_secteurPerso+m_nbColones-1; i<=m_secteurPerso+m_nbColones+1; i++)
    {
        if(i>=0 && i< m_nbColones*m_nbLignes)
        {
            std::vector<Obstacle> obss= m_secteurs.at(i).getCollidables(perso->getTorche(), perso->getPosition());
            for (unsigned int j = 0; j<obss.size(); j++)
            {
                collisionEntre(perso, oldPos, obss.at(j));
            }
        }
    }

    // Collision avec connecteurs
    perso->unsetConnecteur();
    for (unsigned int i = 0; i<m_connecteurs.size(); i++)
    {
        collisionEntre(perso, oldPos, m_connecteurs.at(i), i);
    }

    // Collision avec flammes
    perso->unsetFlamme();
    for (unsigned int i = 0; i<m_flammes.size(); i++)
    {
        collisionEntre(perso, oldPos, m_flammes.at(i));
    }

    // Update du secteur perso
    int colonePerso = perso->getPosition().x/250;
    m_secteurPerso = perso->getPosition().y/250;
    m_secteurPerso*=m_nbLignes;
    m_secteurPerso+=colonePerso;

}


void Television::collisionEntre(Personnage * perso, sf::Vector2f &oldPos, Obstacle &obst)
{
    sf::FloatRect r = perso->getBox();
    sf::Vector2f newPos = perso->getPosition();
    sf::Vector2f deltaPos = newPos-oldPos;
    sf::FloatRect other = obst.getBox();

    float leftOld = r.left-deltaPos.x;
    float topOld = r.top-deltaPos.y;
    float rightOld = leftOld+r.width;
    float bottomOld = topOld+r.height;

    float leftNew = r.left;
    float topNew = r.top;
    float rightNew = leftNew+r.width;
    float bottomNew = topNew+r.height;

    float topObs = other.top;
    float leftObs = other.left;
    float bottomObs = other.top+other.height;
    float rightObs = other.left+other.width;

    if( ! ( (bottomNew <= topObs) || (topNew >= bottomObs) || (leftNew >= rightObs) || (rightNew <= leftObs) ) )// Collision
    {
        if (bottomOld <= topObs) // Arrive par le haut
        {
            newPos.y=topObs-r.height;
            perso->setPosition(newPos);
            perso->setVitesse(perso->getVitesse().x, 0);
            perso->setAuSol(newPos.y);
        }
        else if (topOld >= bottomObs) // Arrive par le bas
        {
            newPos.y=bottomObs;
            perso->setPosition(newPos);
            perso->setVitesse(perso->getVitesse().x, 0);

        }
        else if (leftOld >= rightObs) // Arrive par la droite
        {
            newPos.x=rightObs;
            perso->setPosition(newPos);
            perso->setVitesse(0, perso->getVitesse().y);
        }
        else if (rightOld <= leftObs) // Arrive par la gauche
        {
            newPos.x=leftObs-r.width;
            perso->setPosition(newPos);
            perso->setVitesse(0, perso->getVitesse().y);
        }
        else
        {
            perso->setPosition(oldPos);
            perso->setVitesse(0, 0);
        }
    }

}
void Television::collisionEntre(Personnage * perso, sf::Vector2f &oldPos, Connecteur &obst, int id)
{
    sf::FloatRect r = perso->getBox();
    sf::Vector2f newPos = perso->getPosition();
    sf::Vector2f deltaPos = newPos-oldPos;
    sf::FloatRect other = obst.getBox();

    float leftOld = r.left-deltaPos.x;
    float topOld = r.top-deltaPos.y;
    float rightOld = leftOld+r.width;
    float bottomOld = topOld+r.height;

    float leftNew = r.left;
    float topNew = r.top;
    float rightNew = leftNew+r.width;
    float bottomNew = topNew+r.height;

    float topObs = other.top;
    float leftObs = other.left;
    float bottomObs = other.top+other.height;
    float rightObs = other.left+other.width;

    if( ! ( (bottomNew <= topObs) || (topNew >= bottomObs) || (leftNew >= rightObs) || (rightNew <= leftObs) ) )// Collision
    {
        perso->setConnecteur(id, obst.m_couleur);
    }

}
void Television::collisionEntre(Personnage * perso, sf::Vector2f &oldPos, Flamme &obst)
{
    sf::FloatRect r = perso->getBox();
    sf::Vector2f newPos = perso->getPosition();
    sf::Vector2f deltaPos = newPos-oldPos;
    sf::FloatRect other = obst.getBox();

    float leftOld = r.left-deltaPos.x;
    float topOld = r.top-deltaPos.y;
    float rightOld = leftOld+r.width;
    float bottomOld = topOld+r.height;

    float leftNew = r.left;
    float topNew = r.top;
    float rightNew = leftNew+r.width;
    float bottomNew = topNew+r.height;

    float topObs = other.top;
    float leftObs = other.left;
    float bottomObs = other.top+other.height;
    float rightObs = other.left+other.width;

    if( ! ( (bottomNew <= topObs) || (topNew >= bottomObs) || (leftNew >= rightObs) || (rightNew <= leftObs) ) )// Collision
    {
        perso->setFlamme(obst.m_couleur);
    }

}

void Television::modifieAlimCouleur(int couleur, int posx, int posy, bool ajout)
{
    //Calcul du secteur
    int colone = posx/250;
    int ligne = posy/250;

    for (int i =colone-1; i<=colone+1; i++)
    {
        if(i>=0 && i< m_nbColones)
        {
            for (int j =ligne-1; j<=ligne+1; j++)
            {
                if(j>=0 && j< m_nbLignes)
                {
                    m_secteurs.at(i+j*m_nbColones).modifieAlimCouleur(couleur, ajout);
                }
            }
        }
    }
}

void Television::switchConnecteur(int idConnecteur)
{
    if(idConnecteur<m_connecteurs.size())
    {
        Connecteur &c = m_connecteurs.at(idConnecteur);
        if (c.m_allumee)
        {
            c.etteindre();
            m_score--;
        }
        else
        {
            c.allumer();
            m_score++;
        }
        modifieAlimCouleur(c.m_couleur, c.m_sprite.getPosition().x, c.m_sprite.getPosition().y, c.m_allumee);
    }
}














