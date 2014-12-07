#include "concretebackground.h"
#include "moteur2d.h"
#include <iostream>
#include <typeinfo>

ConcreteBackground::ConcreteBackground(const std::string& imagePath)
{
    //ctor
    m_sprite = 0;
    if (imagePath!="")
    {
        m_sprite = new sf::Sprite;
        m_sprite->setTexture(*Moteur2D::getInstance()->getTexture(imagePath));
        m_image = m_sprite->getTexture()->copyToImage();
    }
    // Il ne s'ajoute plus automatiquement, car c'est le monde qui le dessine maintenant
    // Moteur2D::getInstance()->addConcreteBackground(this);
}

ConcreteBackground::~ConcreteBackground()
{
    //dtor
    if (m_sprite)
        delete m_sprite;
}

bool ConcreteBackground::collidedBy(AnimatedSprite * as, const sf::Vector2f & newObjectPos)
{
    if (!m_sprite)
        return false;



    sf::FloatRect bbox=as->getBox();

    // Point Haut/Gauche se place en haut � gauche de la bbox
    sf::Vector2f posUL = sf::Vector2f(bbox.left, bbox.top);

    sf::Vector2f posDR = posUL;
    posDR.x+=as->getBox().width;
    posDR.y+=as->getBox().height;

    sf::FloatRect sBB = m_sprite->getGlobalBounds();

    // Si hors du background
    if (posDR.x<sBB.left || posDR.y <sBB.top || posUL.x>sBB.width+sBB.left || posUL.y>sBB.height+sBB.top)
    {
        return false;
    }
    //Si Point Haut/gauche trop en haut/gauche
    if (posUL.x<sBB.left)
    {
        posUL.x=sBB.left;
    }
    if (posUL.y<sBB.top)
    {
        posUL.y=sBB.top;
    }

    //Si Point Bas/droite trop en Bas/droite
    if (posDR.x>sBB.width+sBB.left)
    {
        posDR.x=sBB.width+sBB.left;
    }
    if (posDR.y>sBB.height+sBB.top)
    {
        posDR.y=sBB.height+sBB.top;
    }

    // Les positions sont en coordon�es globales
    for (int i = posUL.x; i <posDR.x; i++)
    {
        for (int j = posUL.y; j <posDR.y; j++)
        {
            if (as->isCollidablePoint(sf::Vector2f(i, j)) && m_image.getPixel(i-sBB.left, j-sBB.top).a>128)
                return true;//collision
        }
    }
    return false;

}

void ConcreteBackground::setImage(const std::string& imagePath)
{
    if (!m_sprite)
        m_sprite = new sf::Sprite;
    m_sprite->setTexture(*Moteur2D::getInstance()->getTexture(imagePath));
    m_image = m_sprite->getTexture()->copyToImage();
}



