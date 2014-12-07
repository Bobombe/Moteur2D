#include "connecteur.h"

#include "moteur2d.h"

Connecteur::Connecteur(int couleur, int posX, int posY) : m_couleur(couleur)
{
    //ctor

    m_sprite.setTexture(*Moteur2D::getInstance()->getTexture("ressources\\Connecteur.png"));

    m_sprite.setPosition(posX, posY);
    etteindre();
}

Connecteur::~Connecteur()
{
    //dtor
}

void Connecteur::allumer()
{
    if(m_couleur==1)
        m_sprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
    if(m_couleur==2)
        m_sprite.setTextureRect(sf::IntRect(40, 40, 40, 40));
    if(m_couleur==3)
        m_sprite.setTextureRect(sf::IntRect(40, 80, 40, 40));

    m_allumee=true;
}

void Connecteur::etteindre()
{
    if(m_couleur==1)
        m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
    if(m_couleur==2)
        m_sprite.setTextureRect(sf::IntRect(0, 40, 40, 40));
    if(m_couleur==3)
        m_sprite.setTextureRect(sf::IntRect(0, 80, 40, 40));

    m_allumee=false;
}
