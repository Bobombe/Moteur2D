#include "obstacle.h"
#include "moteur2d.h"

Obstacle::Obstacle(std::string couleur, int tX, int tY, int posX, int posY, bool traversableV)
{
    //ctor
    m_isTraversableVertical = traversableV;

    sf::Texture * t=Moteur2D::getInstance()->getTexture("ressources\\Obstacles\\"+couleur+".png");
    t->setRepeated(true);
    m_sprite.setTexture(*t);
    m_sprite.setTextureRect(sf::IntRect(0, 0, tX, tY));

    m_sprite.setPosition(posX, posY);
}

bool Obstacle::estAPorte(sf::Vector2f pos, float distance)
{
    pos = pos-m_sprite.getPosition();
    if(pos.x*pos.x+pos.y*pos.y>distance*distance)
        return false;
    return true;
}

Obstacle::~Obstacle()
{
    //dtor
}
