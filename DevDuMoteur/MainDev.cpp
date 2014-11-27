#include <iostream>
#include "moteur2d.h"
#include <fixedsprite.h>
#include  "classtest.h"

#include "gravity.h"
#include "concretebackground.h"
#include "monde.h"

#include <SFML/Graphics.hpp>

int main()
{
    std::cout << "GO !" << std::endl;

    Moteur2D* moteur = Moteur2D::getInstance();
    moteur->init(1024, 768);

    Monde m("ressources\\Monde1");
    Monde m2;//"ressources\\Monde2");
    //moteur->addWorld(&m);
    m.set();


    ClassTest ct(&m2);
    Gravity g;
    g.addAllAnimatedSprite();

    moteur->run();
    std::cout << moteur->getTime().asSeconds() << std::endl;
}
