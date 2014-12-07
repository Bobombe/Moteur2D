#include "secteur.h"
#include "moteur2d.h"

#define PorteTorche 200
void Secteur::init()
{
    m_nbSourcesRouges=m_nbSourcesVertes= m_nbSourcesBleues=0;

}
Secteur::Secteur(int px , int py)
{
    //ctor
    m_nbSourcesRouges=m_nbSourcesVertes=m_nbSourcesBleues=0;


    m_textureNoire = Moteur2D::getInstance()->getTexture("ressources\\Fonds\\Noir.png", true);
    m_textureRouge = Moteur2D::getInstance()->getTexture("ressources\\Fonds\\Rouge.png", true);
    m_textureVerte = Moteur2D::getInstance()->getTexture("ressources\\Fonds\\Vert.png", true);
    m_textureBleue = Moteur2D::getInstance()->getTexture("ressources\\Fonds\\Bleu.png", true);
    m_textureJaune = Moteur2D::getInstance()->getTexture("ressources\\Fonds\\Jaune.png", true);
    m_textureCyan = Moteur2D::getInstance()->getTexture("ressources\\Fonds\\Cyan.png", true);
    m_textureMagenta = Moteur2D::getInstance()->getTexture("ressources\\Fonds\\Magenta.png", true);
    m_textureBlanche = Moteur2D::getInstance()->getTexture("ressources\\Fonds\\Blanc.png", true);

    m_fond.setTextureRect(sf::IntRect(0, 0, 250, 250));
    m_fond.setTexture(*m_textureNoire);
    m_fond.setPosition(px, py);

    m_couleurTorche = 0;
    m_posTorche = sf::Vector2f(-1000, -1000);
}

Secteur::~Secteur()
{
    //dtor
}

void Secteur::draw(sf::RenderWindow & window)
{
    updateFond();
    window.draw(m_fond);
    bool drawInverse=false;


    int couleur = getCouleurDeSection();
    int couleurAT = getCouleurAvecTorche();
    bool change = couleur!=couleurAT;
    // Dessine les couleurs normales moins celles cachés par la torche
    if(couleur==1)
    {
        for (unsigned int i = 0; i< m_rouges.size(); i++)
        {
            if(!change || !m_rouges.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_rouges.at(i).m_sprite);
        }
        if(drawInverse)
        for (unsigned int i = 0; i< m_cyans.size(); i++)
        {
            if(!change || !m_cyans.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_cyans.at(i).m_sprite);
        }
    }
    if(couleur==2)
    {
        for (unsigned int i = 0; i< m_verts.size(); i++)
        {
            if(!change || !m_verts.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_verts.at(i).m_sprite);
        }
        if(drawInverse)
        for (unsigned int i = 0; i< m_magentas.size(); i++)
        {
            if(!change || !m_magentas.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_magentas.at(i).m_sprite);
        }
    }
    if(couleur==3)
    {
        for (unsigned int i = 0; i< m_bleus.size(); i++)
        {
            if(!change || !m_bleus.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_bleus.at(i).m_sprite);
        }
        if(drawInverse)
        for (unsigned int i = 0; i< m_jaunes.size(); i++)
        {
            if(!change || !m_jaunes.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_jaunes.at(i).m_sprite);
        }
    }
    if(couleur==4)
    {
        if(drawInverse)
        for (unsigned int i = 0; i< m_bleus.size(); i++)
        {
            if(!change || !m_bleus.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_bleus.at(i).m_sprite);
        }
        for (unsigned int i = 0; i< m_jaunes.size(); i++)
        {
            if(!change || !m_jaunes.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_jaunes.at(i).m_sprite);
        }
    }
    if(couleur==5)
    {
        if(drawInverse)
        for (unsigned int i = 0; i< m_rouges.size(); i++)
        {
            if(!change || !m_rouges.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_rouges.at(i).m_sprite);
        }
        for (unsigned int i = 0; i< m_cyans.size(); i++)
        {
            if(!change || !m_cyans.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_cyans.at(i).m_sprite);
        }
    }
    if(couleur==6)
    {
        if(drawInverse)
        for (unsigned int i = 0; i< m_verts.size(); i++)
        {
            if(!change || !m_verts.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_verts.at(i).m_sprite);
        }
        for (unsigned int i = 0; i< m_magentas.size(); i++)
        {
            if(!change || !m_magentas.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_magentas.at(i).m_sprite);
        }
    }

    //Dessine les couleurs eclairees par la torche
    if (!change)
        return;


    if(couleurAT==1)
    {
        for (unsigned int i = 0; i< m_rouges.size(); i++)
        {
            if(m_rouges.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_rouges.at(i).m_sprite);
        }
        if(drawInverse)
        for (unsigned int i = 0; i< m_cyans.size(); i++)
        {
            if(m_cyans.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_cyans.at(i).m_sprite);
        }
    }
    if(couleurAT==2)
    {
        for (unsigned int i = 0; i< m_verts.size(); i++)
        {
            if(m_verts.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_verts.at(i).m_sprite);
        }
        if(drawInverse)
        for (unsigned int i = 0; i< m_magentas.size(); i++)
        {
            if(m_magentas.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_magentas.at(i).m_sprite);
        }
    }
    if(couleurAT==3)
    {
        for (unsigned int i = 0; i< m_bleus.size(); i++)
        {
            if(m_bleus.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_bleus.at(i).m_sprite);
        }
        if(drawInverse)
        for (unsigned int i = 0; i< m_jaunes.size(); i++)
        {
            if(m_jaunes.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_jaunes.at(i).m_sprite);
        }
    }
    if(couleurAT==4)
    {
        if(drawInverse)
        for (unsigned int i = 0; i< m_bleus.size(); i++)
        {
            if(m_bleus.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_bleus.at(i).m_sprite);
        }
        for (unsigned int i = 0; i< m_jaunes.size(); i++)
        {
            if(m_jaunes.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_jaunes.at(i).m_sprite);
        }
    }
    if(couleurAT==5)
    {
        if(drawInverse)
        for (unsigned int i = 0; i< m_rouges.size(); i++)
        {
            if(m_rouges.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_rouges.at(i).m_sprite);
        }
        for (unsigned int i = 0; i< m_cyans.size(); i++)
        {
            if(m_cyans.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_cyans.at(i).m_sprite);
        }
    }
    if(couleurAT==6)
    {
        if(drawInverse)
        for (unsigned int i = 0; i< m_verts.size(); i++)
        {
            if(m_verts.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_verts.at(i).m_sprite);
        }
        for (unsigned int i = 0; i< m_magentas.size(); i++)
        {
            if(m_magentas.at(i).estAPorte(m_posTorche, PorteTorche))
            window.draw(m_magentas.at(i).m_sprite);
        }
    }


}


void Secteur::addObstacle(int couleur, int tX, int tY, int posX, int posY, bool traversableV)
{
    switch (couleur)
    {
    case 1 :
        m_rouges.push_back(Obstacle("Rouge", tX, tY, posX, posY, traversableV));
        break;
    case 2 :
        m_verts.push_back(Obstacle("Vert", tX, tY, posX, posY, traversableV));
        break;
    case 3 :
        m_bleus.push_back(Obstacle("Bleu", tX, tY, posX, posY, traversableV));
        break;
    case 4 :
        m_jaunes.push_back(Obstacle("Jaune", tX, tY, posX, posY, traversableV));
        break;
    case 5 :
        m_cyans.push_back(Obstacle("Cyan", tX, tY, posX, posY, traversableV));
        break;
    case 6 :
        m_magentas.push_back(Obstacle("Magenta", tX, tY, posX, posY, traversableV));
        break;
    }
}

int Secteur::getCouleurDeSection()
{
    if (estAllimenteEnRouge())
    {
        if(estAllimenteEnVert())
        {
            if(estAllimenteEnBleu())
            {
                return 7; // Blanc
            }
            return 4; // Jaune
        }
        else if(estAllimenteEnBleu())
        {
            return 6; // Magenta
        }
        return 1; // Rouge
    }
    else if (estAllimenteEnVert())
    {
        if(estAllimenteEnBleu())
        {
            return 5; // Cyan
        }
        return 2; // Vert
    }
    else if(estAllimenteEnBleu())
    {
        return 3; // Bleu
    }
    return 0; // Noir
}

int Secteur::getCouleurAvecTorche()
{
    int ret = 0;
    if (m_couleurTorche == 1)
    {
        m_nbSourcesRouges++;
        ret = getCouleurDeSection();
        m_nbSourcesRouges--;
    }
    else if (m_couleurTorche == 2)
    {
        m_nbSourcesVertes++;
        ret = getCouleurDeSection();
        m_nbSourcesVertes--;
    }
    else if (m_couleurTorche == 3)
    {
        m_nbSourcesBleues++;
        ret = getCouleurDeSection();
        m_nbSourcesBleues--;
    }
    else
    {
        ret = getCouleurDeSection();
    }
    return ret;
}

void Secteur::updateFond()
{
    switch (getCouleurDeSection())
    {
    case 0 :
        m_fond.setTexture(*m_textureNoire);
        break;
    case 1 :
        m_fond.setTexture(*m_textureRouge);
        break;
    case 2 :
        m_fond.setTexture(*m_textureVerte);
        break;
    case 3 :
        m_fond.setTexture(*m_textureBleue);
        break;
    case 4 :
        m_fond.setTexture(*m_textureJaune);
        break;
    case 5 :
        m_fond.setTexture(*m_textureCyan);
        break;
    case 6 :
        m_fond.setTexture(*m_textureMagenta);
        break;
    case 7 :
        m_fond.setTexture(*m_textureBlanche);
        break;
    }

}


std::vector<Obstacle> Secteur::getCollidables(int couleurTorche, sf::Vector2f posTorche)
{
    std::vector<Obstacle> ret;
    m_couleurTorche = couleurTorche;
    m_posTorche = posTorche;
    m_posTorche.x+=20;

    switch (getCouleurAvecTorche())
    {
    case 1 :
        //it = ret.insert (it, myarray, myarray+3);
        ret = m_rouges;
        break;
    case 2 :
        ret = m_verts;
        break;
    case 3 :
        ret = m_bleus;
        break;
    case 4 :
        ret = m_jaunes;
        break;
    case 5 :
        ret = m_cyans;
        break;
    case 6 :
        ret = m_magentas;
        break;
    }
    return ret;

}

void Secteur::modifieAlimCouleur(int couleur, bool ajout)
{
    if (couleur==1)//rouge
    {
        if (ajout)
            ajoutRouge();
        else
            supRouge();
    }
    else if (couleur==2)//vert
    {
        if (ajout)
            ajoutVert();
        else
            supVert();
    }
    else if (couleur==3)//bleu
    {
        if (ajout)
            ajoutBleu();
        else
            supBleu();
    }
}




