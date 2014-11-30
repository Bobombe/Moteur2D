#include "monde.h"

#include "moteur2d.h"

#include <iostream>
#include <fstream>

Monde::Monde(std::string folderPath)
{
    //ctor
    m_isLoaded = false;
    m_background = 0;
    m_concreteBackground = 0;
    m_bgIndex = -1;
    m_cbgIndex = -1;
    m_position = sf::Vector2f(0, 0);
    m_taille = sf::Vector2f(0, 0);
    m_folderPath = folderPath;
    m_loadThread = new sf::Thread(&Monde::loadInThread, this);

    if (folderPath.compare("")!=0)
    {
        load();
    }
}

Monde::~Monde()
{
    //dtor
    if (m_background)
        delete m_background;
    if (m_concreteBackground)
        delete m_concreteBackground;
}

void Monde::load(std::string folderPath)
{
    if (!m_isLoaded)
    {
        if (folderPath.compare("")!=0)
            m_folderPath = folderPath;

        if(m_folderPath.compare("")!=0)
            m_loadThread->launch();
        //loadInThread();
    }

}

void Monde::loadInThread()
{
    m_background = new sf::Sprite;
    m_background->setTexture(*Moteur2D::getInstance()->getTexture(m_folderPath+"\\bg.png"));
    m_concreteBackground = new ConcreteBackground(m_folderPath+"\\cbg.png");
    //Lecture de monde.txt
    std::ifstream file((m_folderPath+"\\monde.txt").c_str(), std::ios::in);
    int px, py, w, h;
    file>>m_position.x;
    file>>m_position.y;
    file>>m_taille.x;
    file>>m_taille.y;

    m_background->setPosition(m_position);
    m_concreteBackground->setPosition(m_position);
    set();



    std::cout << "loaded " << std::endl;
    m_isLoaded = true;

    // Lecture de fichier de la taille et position du monde (monde.txt)
}

void Monde::set()
{
    if (m_isLoaded)
    {
        if(m_bgIndex==-1)
        {
            m_bgIndex = Moteur2D::getInstance()->addPreDrawable(m_background);
        }
        if(m_cbgIndex==-1)
        {
            m_cbgIndex = Moteur2D::getInstance()->addConcreteBackground(m_concreteBackground);
        }

        Moteur2D::getInstance()->getView()->setWorldBoundaries(sf::FloatRect(m_position.x, m_position.y, m_taille.x, m_taille.y));

    }
}

void Monde::wait()
{
    if (!m_isLoaded)
    {
        m_loadThread->wait();
    }
}

void Monde::waitAndSet()
{
    wait();
    set();
}

void Monde::unset()
{
    if(m_bgIndex>-1)
    {
        Moteur2D::getInstance()->deletePreDrawable(m_bgIndex);
        m_bgIndex = -1;

    }
    if(m_cbgIndex>-1)
    {
        Moteur2D::getInstance()->deleteConcreteBackground(m_cbgIndex);
        m_cbgIndex = -1;
    }
}
