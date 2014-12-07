#include "view.h"
#include "moteur2d.h"

View::View()
{
    //ctor
    m_worldBoundariesSet = false;
}

View::~View()
{
    //dtor
}

void View::move(const sf::Vector2f &offset)
{
    sf::View::move(offset);
    Moteur2D::getInstance()->updateView();
}

void View::move(float offsetX, float offsetY)
{
    sf::View::move(offsetX, offsetY);
    Moteur2D::getInstance()->updateView();
}

void View::moveWithCharacter(const sf::Vector2f &position)
{

    sf::Vector2f posInView = getPosInView(position);
    sf::Vector2f center = getCenter();
    sf::Vector2f size = getSize();
    sf::Vector2f newCenter = center;
    if (posInView.x< size.x/4)
    {
        newCenter.x = position.x+size.x/4;
    }
    else if (posInView.x> 3*size.x/4)
    {
        newCenter.x = position.x-size.x/4;
    }
    if (posInView.y< size.y/4)
    {
        newCenter.y = position.y+size.y/4;
    }
    else if (posInView.y> 3*size.y/4)
    {
        newCenter.y = position.y-size.y/4;
    }

    if (m_worldBoundariesSet)
    {
        if(newCenter.x<m_worldBoundaries.left+size.x/2)
        {
            newCenter.x=m_worldBoundaries.left+size.x/2;
        }
        if(newCenter.x>m_worldBoundaries.left+m_worldBoundaries.width-size.x/2)
        {
            newCenter.x=m_worldBoundaries.left+m_worldBoundaries.width-size.x/2;
        }
        if(newCenter.y<m_worldBoundaries.top+size.y/2)
        {
            newCenter.y=m_worldBoundaries.top+size.y/2;
        }
        if(newCenter.y>m_worldBoundaries.top+m_worldBoundaries.height-size.y/2)
        {
            newCenter.y=m_worldBoundaries.top+m_worldBoundaries.height-size.y/2;
        }
    }

    setCenter(newCenter);
    Moteur2D::getInstance()->updateView();
}

void View::zoomOnMouse(float factor)
{
    sf::Vector2f mp = getMouseInWorld();
    zoom(factor);

    mp -= getMouseInWorld();
    move(mp);
}


sf::Vector2f View::getMouseInWorld()
{
    const sf::RenderWindow &win = Moteur2D::getInstance()->getWindow() ;
    sf::Vector2i mPos = sf::Mouse::getPosition(win );
    sf::Vector2f ret;
    ret.x = (float)mPos.x / win.getSize().x;
    ret.x *= getSize().x;
    ret.x += getCenter().x;
    ret.x -= getSize().x/2;

    ret.y = (float)mPos.y / win.getSize().y;
    ret.y *= getSize().y;
    ret.y += getCenter().y;
    ret.y -= getSize().y/2;

    return ret;
}


sf::Vector2f View::getPosInView(const sf::Vector2f& posInWorld)
{
    sf::Vector2f ret = posInWorld;
    ret -= getCenter();
    ret.x+= getSize().x/2.;
    ret.y+= getSize().y/2.;

/*
    const sf::RenderWindow &win = Moteur2D::getInstance()->getWindow() ;
    sf::Vector2i mPos = sf::Mouse::getPosition(win );
    ret.x = (float)mPos.x / win.getSize().x;
    ret.x *= getSize().x;
    ret.x += getCenter().x;
    ret.x -= getSize().x/2;

    ret.y = (float)mPos.y / win.getSize().y;
    ret.y *= getSize().y;
    ret.y += getCenter().y;
    ret.y -= getSize().y/2;
//*/
    return ret;
}

float View::getZoom()
{
    return getSize().x / Moteur2D::getInstance()->getWindow().getSize().x;
}

void View::setWorldBoundaries(const sf::FloatRect& wb)
{
    m_worldBoundaries.left = wb.left;
    m_worldBoundaries.top = wb.top;
    m_worldBoundaries.height = wb.height;
    m_worldBoundaries.width = wb.width;

    m_worldBoundariesSet = true;
}












