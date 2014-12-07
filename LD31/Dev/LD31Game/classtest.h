#ifndef CLASSTEST_H
#define CLASSTEST_H

#include "mouselistener.h"
#include "ketboardlistener.h"
#include "updatable.h"
#include "animatedsprite.h"
#include "monde.h"

#include <SFML/Graphics.hpp>

class ClassTest : public KeyboardListener, public MouseListener, public AnimatedSprite
{
    public:
        ClassTest();
        ClassTest(Monde * m);
        virtual ~ClassTest();

        virtual void buttonPressed(sf::Event::MouseButtonEvent mbe);
        virtual void buttonReleased(sf::Event::MouseButtonEvent mbe){}
        virtual void mouseMoved(sf::Event::MouseMoveEvent mme){}
        virtual void mouseWheel(sf::Event::MouseWheelEvent mwe);
        virtual void update(float seconds);


        virtual void keyPressed(sf::Keyboard::Key k);
        virtual void keyReleased(sf::Keyboard::Key k);
    protected:
        Monde * m_monde;
        bool m_bool;

    private:
};

#endif // CLASSTEST_H
