#include <iostream>
#include "moteur2d.h"
#include <fixedsprite.h>
#include  "classtest.h"

#include "gravity.h"
#include "concretebackground.h"
#include "monde.h"
#include "television.h"
#include "personnage.h"
#include <fstream>

#include <SFML/Graphics.hpp>

int main()
{

    // Le Jeu
    Moteur2D* moteur = Moteur2D::getInstance();
    moteur->init(1024, 768);

    Television t("Ecran1");

    Personnage p(t);

    moteur->run();


    /*/ // Le Generateur


    std::string ecran = "Ecran1";
    sf::Image r;
    sf::Image v;
    sf::Image b;
    sf::Image ja;
    sf::Image c;
    sf::Image m;
    sf::Image cr;
    sf::Image cv;
    sf::Image cb;
    sf::Image tr;
    sf::Image tv;
    sf::Image tb;
    r.loadFromFile("ressources\\"+ecran + "\\EcranRouge.png");
    v.loadFromFile("ressources\\"+ecran + "\\EcranVert.png");
    b.loadFromFile("ressources\\"+ecran + "\\EcranBleu.png");
    ja.loadFromFile("ressources\\"+ecran + "\\EcranJaune.png");
    c.loadFromFile("ressources\\"+ecran + "\\EcranCyan.png");
    m.loadFromFile("ressources\\"+ecran + "\\EcranMagenta.png");
    cr.loadFromFile("ressources\\"+ecran + "\\EcranConnecteursRouges.png");
    cv.loadFromFile("ressources\\"+ecran + "\\EcranConnecteursVerts.png");
    cb.loadFromFile("ressources\\"+ecran + "\\EcranConnecteursBleus.png");
    tr.loadFromFile("ressources\\"+ecran + "\\EcranTorchesRouges.png");
    tv.loadFromFile("ressources\\"+ecran + "\\EcranTorchesVertes.png");
    tb.loadFromFile("ressources\\"+ecran + "\\EcranTorchesBleues.png");
    unsigned int tx = r.getSize().x;
    unsigned int ty = r.getSize().y;

    // Verif coherence
    if(tx!=v.getSize().x || tx!=v.getSize().x || tx!=b.getSize().x || tx!=ja.getSize().x || tx!=c.getSize().x || tx!=m.getSize().x)
    {
        std::cout << "Taille non correspondante !" << std::endl;
        return -1;
    }
    if(ty!=v.getSize().y || ty!=v.getSize().y || ty!=b.getSize().y || ty!=ja.getSize().y || ty!=c.getSize().y || ty!=m.getSize().y)
    {
        std::cout << "Taille non correspondante !" << std::endl;
        return -1;
    }

    std::ofstream f(("ressources\\"+ecran + "\\"+ecran+".txt").c_str(), std::ios::out | std::ios::trunc);
    f << "#tailleX tailleY"<< std::endl <<"2000 2000"<< std::endl <<"#Obstacles (color = de 1 a 6, R, V, B, J, C, M) :"<< std::endl <<"#color tX tY posX posY";

    std::cout << "Obstacles"<<std::endl;
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (r.getPixel(i, j).a>128)
            {
                f << std::endl <<"1 " << i*10 << " " << j*10;
            }
        }
    }
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (v.getPixel(i, j).a>128)
            {
                f << std::endl <<"2 " << i*10 << " " << j*10;
            }
        }
    }
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (b.getPixel(i, j).a>128)
            {
                f << std::endl <<"3 " << i*10 << " " << j*10;
            }
        }
    }
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (ja.getPixel(i, j).a>128)
            {
                f << std::endl <<"4 " << i*10 << " " << j*10;
            }
        }
    }
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (c.getPixel(i, j).a>128)
            {
                f << std::endl <<"5 " << i*10 << " " << j*10;
            }
        }
    }
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (m.getPixel(i, j).a>128)
            {
                f << std::endl <<"6 " << i*10 << " " << j*10;
            }
        }
    }
    //Connecteurs
    std::cout << "Connecteurs"<<std::endl;
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (cr.getPixel(i, j).a>128)
            {
                f << std::endl <<"11 " << i*10 << " " << j*10;
            }
        }
    }
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (cv.getPixel(i, j).a>128)
            {
                f << std::endl <<"12 " << i*10 << " " << j*10;
            }
        }
    }
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (cb.getPixel(i, j).a>128)
            {
                f << std::endl <<"13 " << i*10 << " " << j*10;
            }
        }
    }
    //Torches
    std::cout << "Torches"<<std::endl;
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (tr.getPixel(i, j).a>128)
            {
                f << std::endl <<"21 " << i*10 << " " << j*10;
            }
        }
    }
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (tv.getPixel(i, j).a>128)
            {
                f << std::endl <<"22 " << i*10 << " " << j*10;
            }
        }
    }
    for (unsigned int i = 0; i<tx; i++)
    {
        for (unsigned int j = 0; j<ty; j++)
        {
            if (tb.getPixel(i, j).a>128)
            {
                f << std::endl <<"23 " << i*10 << " " << j*10;
            }
        }
    }
system("pause");

    //*/
}
