#include "fixedsprite.h"
#include "moteur2d.h"
#include <typeinfo>

// CONSTRUCTORS
FixedSprite::FixedSprite(bool addToFixedSpriteList)
{
    //ctor
    m_indexOfSprite = -1;
    if (addToFixedSpriteList)
        Moteur2D::getInstance()->addFixedSprite(this);
}

FixedSprite::FixedSprite(const std::string& imagePath, bool addToFixedSpriteList) : FixedSprite(addToFixedSpriteList)
{
    //ctor
    if (imagePath != "")
        setSprite(imagePath);
    setPosition(sf::Vector2f(0, 0));
}

FixedSprite::FixedSprite(const sf::Vector2f& pos, const std::string& imagePath, bool addToFixedSpriteList) : FixedSprite(addToFixedSpriteList)
{
    //ctor
    if (imagePath != "")
        setSprite(imagePath);
    setPosition(pos);
}

// DESTRUCTORS
FixedSprite::~FixedSprite()
{
    //dtor
    Moteur2D::getInstance()->deleteFixedSprite(this);
    if (m_sprite)
    {
        delete m_sprite;
    }

    if (m_indexOfSprite>=0)
    {
        Moteur2D::getInstance()->deleteDrawable(m_indexOfSprite);
    }
}

// METHODES
bool FixedSprite::isCollidablePoint(sf::Vector2f pointInGlobalCoordinate)
{
        //on transforme pointInGlobalCoordinate en coordonnées locales
        pointInGlobalCoordinate=m_sprite->getTransform().getInverse().transformPoint(pointInGlobalCoordinate);

        // Si compris dans le sprite
        if(pointInGlobalCoordinate.x>0 && pointInGlobalCoordinate.y>0&&
           pointInGlobalCoordinate.x<m_sprite->getTextureRect().width && pointInGlobalCoordinate.y<m_sprite->getTextureRect().height)
        {
            // Return true if pixel.alpha>128
            return (m_image.getPixel(pointInGlobalCoordinate.x, pointInGlobalCoordinate.y).a)>128;
        }
        return false;

}
void FixedSprite::jesuis()
{
    std::cout << "FixedSprite numero " << m_indexOfSprite << std::endl;
}

// SETTERS
void FixedSprite::setSprite(const std::string& imagePath)
{
    //m_drawableObject = Moteur2D::getInstance()->addSprite(imagePath);

    m_sprite = new sf::Sprite;
    m_sprite->setTexture(*Moteur2D::getInstance()->getTexture(imagePath));
    m_bBox = m_sprite->getGlobalBounds();

    m_indexOfSprite = Moteur2D::getInstance()->addDrawable(m_sprite);

    m_image = m_sprite->getTexture()->copyToImage();
    m_size.x = m_bBox.width;
    m_size.y=m_bBox.height;

}

void FixedSprite::setPosition(const sf::Vector2f &pos)
{
    m_sprite->setPosition(pos);
    m_bBox = m_sprite->getGlobalBounds();
}

void FixedSprite::setRotation(float degree)
{
    m_sprite->setRotation(degree);
    m_bBox = m_sprite->getGlobalBounds();
}

void FixedSprite::setScale(float scale)
{
    m_sprite->scale(scale, scale);
    m_bBox = m_sprite->getGlobalBounds();
    m_size.x = m_bBox.width;
    m_size.y=m_bBox.height;
}
// Travail en cour : MàJ du code suivant, puis ajout du code depuis FixedObject. Ensuite faire de même avec AnimatedSprite


// GETTERS
sf::Vector2f FixedSprite::getPosition()
{
    return m_sprite->getPosition();
}

sf::FloatRect FixedSprite::getBox()
{
    return m_bBox;
}
sf::Sprite* FixedSprite::getSprite()
{
    return m_sprite;
}
sf::Vector2f FixedSprite::getSize()
{
    return m_size;
}
float FixedSprite::getWidth()
{
    return m_size.x;
}
float FixedSprite::getHeight()
{
    return m_size.y;
}







