#include "personnage.h"
#include <iostream>
#include "moteur2d.h"

Personnage::Personnage(Television &tele) : AnimatedSprite("ressources\\Personage.PNG",sf::Vector2f(0, 0)), m_tele(tele)
{
    //ctor

    m_posDepart.x = 5;
    m_posDepart.y = 2000-61;
    init();
}

void Personnage::init()
{

    m_droite = m_gauche = m_jump = false;
    m_auSol = -1;// Positions négatives interdites => n'est pas au sol
    m_sprite->setTextureRect(sf::IntRect(0, 0, 40, 60));
    m_orienteDroite = true;
    m_currentAction = Arret;
    m_torche = Etteinte;
    m_couleurTorche = 0;
    m_idConnecteur = -1;
    m_couleurConnecteur = -1;
    setPosition(m_posDepart);

}

Personnage::~Personnage()
{
    //dtor
}

void Personnage::update(float seconds)
{
    int vmax = 6, acc = 40; // m/s
    int g = 40, accSaut = 10;
    int pixParMettre = 100;
    vmax*=pixParMettre;
    acc*=pixParMettre;
    g*=pixParMettre;
    accSaut*=pixParMettre;
     /////////////////////////////////////////
    //       DEPLACEMENTS HORIZONTAUX      //
   /////////////////////////////////////////
    if (m_droite && !m_gauche)
    {
        m_vit.x+=acc*seconds;
        if (m_vit.x>vmax)
        {
            m_vit.x=vmax;
        }
        m_orienteDroite = true;
    }
    else if (m_gauche && !m_droite)
    {
        m_vit.x-=acc*seconds;
        if (m_vit.x<-vmax)
        {
            m_vit.x=-vmax;
        }
        m_orienteDroite = false;
    }
    else
    {
        if (m_vit.x > 0)
        {
            //m_orienteDroite = true;
            m_vit.x-=acc/1.2*seconds;
            if (m_vit.x<0)
            {
                m_vit.x=0;
            }
        }
        else if (m_vit.x < 0)
        {
            //m_orienteDroite = false;
            m_vit.x+=acc/1.2*seconds;
            if (m_vit.x>0)
            {
                m_vit.x=0;
            }
        }
    }
     /////////////////////////////////////////
    //        DEPLACEMENTS VERTICAUX       //
   /////////////////////////////////////////
    m_vit.y+=g*seconds; // gravité
    if(m_auSol==getPosition().y)
    {
        if(m_jump)
        {
            m_auSol=-1;
            m_vit.y = -accSaut;
        }
    }
    else
    {
        m_auSol = -1;
    }

     /////////////////////////////////////////
    //           Update du Sprite          //
   /////////////////////////////////////////
    int px = m_orienteDroite ? 0: 40;
    int py = 0;
    switch (m_torche)
    {
    case Etteinte:
        py = 180;
        break;
    case TorcheRouge:
        py = 0;
        break;
    case TorcheVerte:
        py = 60;
        break;
    case TorcheBleue:
        py = 120;
        break;
    }
    m_sprite->setTextureRect(sf::IntRect(px, py, 40, 60));
    /*
    if (m_orienteDroite)
    {
        m_sprite->setTextureRect(sf::IntRect(0, 0, 40, 60));
    }
    else
    {
        m_sprite->setTextureRect(sf::IntRect(40, 0, 40, 60));
    }//*/

    AnimatedSprite::update(seconds);
    Moteur2D::getInstance()->getView()->moveWithCharacter(getPosition());
}

void Personnage::keyPressed(sf::Keyboard::Key k)
{
    if(k==sf::Keyboard::S) //Interact
    {
        if(m_couleurConnecteur == m_torche)
            m_tele.switchConnecteur(m_idConnecteur);

        if (m_flamme>0)
        {
            changeTorche(m_flamme, true);
            m_couleurTorche = m_flamme;
        }
    }
    if(k==sf::Keyboard::D) // Allumer/etteindre
    {
        changeTorche(m_couleurTorche);
    }
    if(k==sf::Keyboard::Left)
    {
        m_gauche=true;
    }
    if(k==sf::Keyboard::Right)
    {
        m_droite=true;
    }
    if(k==sf::Keyboard::Up || k==sf::Keyboard::Space)
    {
        if (m_auSol==getPosition().y)
            m_jump=true;
    }
    if(k==sf::Keyboard::BackSpace)
    {
        init();
        m_tele.init();

    }

    /*
    if(k==sf::Keyboard::R)
    {
        changeTorche(1);
    }
    if(k==sf::Keyboard::G)
    {
        changeTorche(2);
    }
    if(k==sf::Keyboard::B)
    {
        changeTorche(3);
    }
    if(k==sf::Keyboard::Numpad1)
    {
        m_tele.modifieAlimCouleur(1, getPosition().x, getPosition().y);
    }
    if(k==sf::Keyboard::Numpad2)
    {
        m_tele.modifieAlimCouleur(2, getPosition().x, getPosition().y);
    }
    if(k==sf::Keyboard::Numpad3)
    {
        m_tele.modifieAlimCouleur(3, getPosition().x, getPosition().y);
    }
    if(k==sf::Keyboard::Numpad4)
    {
        m_tele.modifieAlimCouleur(1, getPosition().x, getPosition().y, false);
    }
    if(k==sf::Keyboard::Numpad5)
    {
        m_tele.modifieAlimCouleur(2, getPosition().x, getPosition().y, false);
    }
    if(k==sf::Keyboard::Numpad6)
    {
        m_tele.modifieAlimCouleur(3, getPosition().x, getPosition().y, false);
    }//*/
}

void Personnage::keyReleased(sf::Keyboard::Key k)
{
    if(k==sf::Keyboard::Left)
    {
        m_gauche=false;
    }
    if(k==sf::Keyboard::Right)
    {
        m_droite=false;
    }
    if(k==sf::Keyboard::Up || k==sf::Keyboard::Space)
    {
        m_jump=false;
    }
}




void Personnage::checkCollision(float seconds, sf::Vector2f oldPos)
{
    // newPos déjà calculée et settée
    m_tele.collisionPersonnage(this, oldPos);
    //
}

void Personnage::changeTorche(int couleur, bool keep)
{
    if (couleur == 1)
    {
        if (m_torche == TorcheRouge && !keep)
        {
            m_torche = Etteinte;
        }
        else
        {
            m_torche = TorcheRouge;
        }
    }
    else if (couleur == 2)
    {
        if (m_torche == TorcheVerte && !keep)
        {
            m_torche = Etteinte;
        }
        else
        {
            m_torche = TorcheVerte;
        }
    }
    else if (couleur == 3)
    {
        if (m_torche == TorcheBleue && !keep)
        {
            m_torche = Etteinte;
        }
        else
        {
            m_torche = TorcheBleue;
        }
    }
}



