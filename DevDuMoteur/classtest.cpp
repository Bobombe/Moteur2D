#include "classtest.h"
#include <iostream>
#include "moteur2d.h"
#include "view.h"
#include <typeinfo>

ClassTest::ClassTest() : AnimatedSprite("ressources\\PersoTP.PNG",sf::Vector2f(200, 630))
{
    //ctor

    sf::Sprite* s = new sf::Sprite;
    sf::Texture* t = new sf::Texture;

    try
    {
        sf::Sprite& sprite = *m_sprite;

        sf::Image image = sprite.getTexture()->copyToImage();
        t->loadFromImage(image);
        s->setTexture(*t);
        s->setPosition(400, 400);
        Moteur2D::getInstance()->addPostDrawable(s);
        std::cout << "ok" << std::endl;
    }
    catch (const std::bad_cast& e)
    {
        //std::cerr << e.what() << std::endl;
    }

    m_bool = false;
}

ClassTest::ClassTest(Monde * m) : ClassTest()
{
    m_monde = m;
}
ClassTest::~ClassTest()
{
    //dtor
}

void ClassTest::buttonPressed(sf::Event::MouseButtonEvent mbe)
{
    setVitesse(Moteur2D::getInstance()->getView()->getMouseInWorld()-getPosition());
        m_monde->set();
    /*
    if(m_bool)
    {
        m_monde->set();
    }
    else
    {
        m_monde->unset();
    }
    m_bool = !m_bool;
    //*/

}

void ClassTest::mouseWheel(sf::Event::MouseWheelEvent mwe)
{
    if (mwe.delta<0)
    {
        Moteur2D::getInstance()->getView()->zoomOnMouse(2);
    }
    else
    {
        Moteur2D::getInstance()->getView()->zoomOnMouse(0.5);
    }
}

void ClassTest::update(float seconds)
{
    AnimatedSprite::update(seconds);
    Moteur2D::getInstance()->getView()->moveWithCharacter(getPosition());
}

void ClassTest::keyPressed(sf::Keyboard::Key k)
{
    std::cout << k << std::endl;
    if(k==25)
    {
        m_vit+= sf::Vector2f(0, -250);
    }
    if(k==16)
    {
        m_vit+= sf::Vector2f(-250, 0);
    }
    if(k==3)
    {
        m_vit+= sf::Vector2f(250, 0);
    }
}

void ClassTest::keyReleased(sf::Keyboard::Key k)
{
    //std::cout << k << std::endl;
}


