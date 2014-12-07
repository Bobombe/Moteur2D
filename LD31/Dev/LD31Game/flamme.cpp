#include "flamme.h"

#include "moteur2d.h"

Flamme::Flamme(int couleur, int posX, int posY) : m_couleur(couleur)
{
    //ctor

    m_sprite.setTexture(*Moteur2D::getInstance()->getTexture("ressources\\Flammes.png"));

    m_sprite.setPosition(posX, posY);
    m_sprite.setTextureRect(sf::IntRect(0, 20*(couleur-1), 20, 20));

}

Flamme::~Flamme()
{
    //dtor
}
