#include "animatedsprite.h"
#include <iostream>
#include "moteur2d.h"

AnimatedSprite::AnimatedSprite() : FixedSprite(false)
{
    //ctor
    m_vit = sf::Vector2f(0, 0);
    Moteur2D::getInstance()->addAnimatedSprite(this);
}

AnimatedSprite::AnimatedSprite(const std::string& imagePath, const sf::Vector2f& pos, sf::Vector2f vit) : FixedSprite(pos, imagePath, false)
{
    //ctor
    m_vit = vit;
    Moteur2D::getInstance()->addAnimatedSprite(this);
}

AnimatedSprite::AnimatedSprite(const sf::Vector2f& pos, const std::string& imagePath) : FixedSprite(pos, imagePath, false)
{
    //ctor
    m_vit = sf::Vector2f(0, 0);
    Moteur2D::getInstance()->addAnimatedSprite(this);
}

AnimatedSprite::~AnimatedSprite()
{
    //dtor

}

//GETTERS
sf::Vector2f AnimatedSprite::getVitesse()
{
    return m_vit;
}


// SETTERS
void AnimatedSprite::setVitesse(const sf::Vector2f& v)
{
    m_vit.x= v.x;
    m_vit.y = v.y;
}

void AnimatedSprite::update(float seconds)
{
    // Calcule la nouvelle position sans collision
    sf::Vector2f oldPos = getPosition();
    sf::Vector2f newPos = oldPos+m_vit*seconds;
    setPosition( newPos);

    if (true)//m_isCollidable)
    {
        //setPosition(checkCollision(seconds));
        checkCollision(seconds, oldPos);
    }
    else
    {
        setPosition(getPosition()+m_vit*seconds);
    }
}

// PRIVATES METHODES

void AnimatedSprite::checkCollision(float seconds, sf::Vector2f oldPos)
{
    sf::Vector2f newPos = getPosition();


    // Pour chaque objets
    // Collisions avec les objets fixes
    std::vector <FixedSprite*> fss = Moteur2D::getInstance()->getFixedSprites();
    for (unsigned int i = 0; i<fss.size(); i++)
    {
        FixedSprite* fs = fss.at(i);
        if ((*fs)!=(*this) && collideWith(fs))
        {
            // On traite la collision
            applyCollision(fs, oldPos);
            return ;
        }

    }
    // Collisions avec les objets mouvants.
    std::vector <AnimatedSprite*> ass = Moteur2D::getInstance()->getAnimatedSprites();
    for (unsigned int i = 0; i<ass.size(); i++)
    {
        AnimatedSprite* as = ass.at(i);
        if ((*as)!=(*this) && collideWith(as))
        {
            // On traite la collision
            applyCollision(as, oldPos);
            return;
        }
    }
    // Collisions avec les arrière plans concrets.
    std::map <int, ConcreteBackground*> cbs = Moteur2D::getInstance()->getConcreteBackgrounds();
    for (std::map<int,ConcreteBackground*>::iterator it=cbs.begin(); it!=cbs.end(); ++it)
    {
        if ((it->second)->collidedBy(this, newPos))
        {
            // On traite la collision
            m_vit.x=0;
            m_vit.y=0;
            setPosition( oldPos);
            return;
        }
    }
}

void AnimatedSprite::applyCollision(FixedSprite * fs, sf::Vector2f oldPos)
{
    m_vit.x=0;
    m_vit.y=0;
    setPosition( oldPos);
}

bool AnimatedSprite::collideWith(const sf::FloatRect &other, const sf::Vector2f & newPos)
{
    sf::FloatRect r = getBox();
    sf::Vector2f p = getPosition();

    float left1 = newPos.x-p.x+r.left;
    float top1 = newPos.y-p.y+r.top;
    float right1 = left1+r.width;
    float bottom1 = top1+r.height;

    float bottom2 = other.top+other.height;
    float right2 = other.left+other.width;


    return ! (
    (bottom1 < other.top) ||
    (top1 > bottom2) ||
    (left1 > right2) ||
    (right1 < other.left) );

}


bool AnimatedSprite::collideWith(FixedSprite * fs)
{
    sf::FloatRect fsBox = fs->getBox();

// Point Haut/Gauche se place en haut à gauche de la bbox
    sf::Vector2f posUL = sf::Vector2f(m_bBox.left, m_bBox.top);

    sf::Vector2f posDR = posUL;
    posDR.x+=m_bBox.width;
    posDR.y+=m_bBox.height;

    // Si hors de l'objet
    if (posDR.x<fsBox.left || posDR.y <fsBox.top || posUL.x>fsBox.width+fsBox.left || posUL.y>fsBox.height+fsBox.top)
    {
        return false;
    }
    //Si Point Haut/gauche trop en haut/gauche
    if (posUL.x<fsBox.left)
    {
        posUL.x=fsBox.left;
    }
    if (posUL.y<fsBox.top)
    {
        posUL.y=fsBox.top;
    }

    //Si Point Bas/droite trop en Bas/droite
    if (posDR.x>fsBox.width+fsBox.left)
    {
        posDR.x=fsBox.width+fsBox.left;
    }
    if (posDR.y>fsBox.height+fsBox.top)
    {
        posDR.y=fsBox.height+fsBox.top;
    }

    // Les positions sont en coordonées globales
    for (int i = posUL.x; i <posDR.x; i++)
    {
        for (int j = posUL.y; j <posDR.y; j++)
        {
            if (isCollidablePoint(sf::Vector2f(i, j)) && fs->isCollidablePoint(sf::Vector2f(i, j)))
            {
                return true;
            }
        }
    }
    return false;

}










