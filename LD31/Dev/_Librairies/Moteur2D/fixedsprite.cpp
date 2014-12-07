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
    m_currentAnimation = "";
    currentTextureId = 0;
    m_time = 0;
    m_fps = 4;
}

FixedSprite::FixedSprite(const std::string& imagePath, bool addToFixedSpriteList) : FixedSprite(addToFixedSpriteList)
{
    //ctor
    if (imagePath != "")
        setSprite(imagePath);
    setPosition(sf::Vector2f(0, 0));
    m_currentAnimation = "";
    currentTextureId = 0;
    m_time = 0;
    m_fps = 4;
}

FixedSprite::FixedSprite(const sf::Vector2f& pos, const std::string& imagePath, bool addToFixedSpriteList) : FixedSprite(addToFixedSpriteList)
{
    //ctor
    if (imagePath != "")
        setSprite(imagePath);
    setPosition(pos);
    m_currentAnimation = "";
    currentTextureId = 0;
    m_time = 0;
    m_fps = 4;
}

FixedSprite::FixedSprite(const std::string& texturePath, const sf::Vector2f& size, int nbLignes, int nbColumns, bool addToFixedSpriteList) : FixedSprite(addToFixedSpriteList)
{
    //ctor
    if (texturePath != "")
    {
        setSprite(texturePath);
        m_sprite->setTextureRect(sf::IntRect(40, 0, size.x, size.y));
    }
    setPosition(sf::Vector2f(90, 60));
    m_currentAnimation = "";
    currentTextureId = 0;
    m_time = 0;
    m_sizeSprite = size;
    m_fps = 4;
    m_columns = nbColumns;
    m_lignes = nbLignes;
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

void FixedSprite::addAnimation(std::string name, int firstImageId, int lastImageId)
{
    if (name != "")
    {

        struct animationTexture aT;
        aT.first = firstImageId;
        aT.last = lastImageId;

        m_animations.insert(std::pair<std::string, struct animationTexture>(name, aT));
    }

}

void FixedSprite::updateTexture(float s)
{
    m_time+=s;
    if (m_time>(1./m_fps))//4 images par seconde
    {
        struct animationTexture aT= m_animations.at(m_currentAnimation);


        currentTextureId++;
        if (currentTextureId>aT.last)
        {
            currentTextureId = aT.first;
        }
        m_time=0;
        int c = currentTextureId/m_columns;
        c=currentTextureId-c*m_columns;
        m_sprite->setTextureRect(sf::IntRect(m_sizeSprite.x*c, m_sizeSprite.y*(currentTextureId/m_columns), m_sizeSprite.x, m_sizeSprite.y));
    }
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

void FixedSprite::setPosition(float x, float y)
{
    m_sprite->setPosition(x, y);
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
    m_animations.end();
}

void FixedSprite::setAnimation(std::string name)
{
    if (name =="" || m_animations.find(name)!= m_animations.end())
    {
        m_currentAnimation = name;
        currentTextureId = m_animations.at(name).first;
        m_sprite->setTextureRect(sf::IntRect(m_sizeSprite.x*currentTextureId, 0, m_sizeSprite.x, m_sizeSprite.y));
        Moteur2D::getInstance()->addAnimatedTextures(this);
    }

}

void FixedSprite::setFps(int fps)
{
    m_fps = fps;
}

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







