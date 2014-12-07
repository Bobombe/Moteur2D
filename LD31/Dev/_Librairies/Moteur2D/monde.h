#ifndef MONDE_H
#define MONDE_H

#include <SFML/Graphics.hpp>

#include <string>
#include "concretebackground.h"

class Monde
{
    public:
        Monde(std::string folderPath = "");
        virtual ~Monde();

        virtual void load(std::string folderPath = "");

        // Charge/décharge le monde dans le Moteur
        void wait();
        void set();
        void waitAndSet();
        void unset();

    protected:
        // Methodes protected
        virtual void loadInThread();

        //Thread pour lancer le load
        sf::Thread *m_loadThread;

        // Path du dossier contenant le monde
        std::string m_folderPath;

        bool m_isLoaded;

        // Le font pour du décord
        sf::Sprite * m_background;
        int m_bgIndex;
        ConcreteBackground * m_concreteBackground;
        int m_cbgIndex;

        // TO DO : AnimatedSprite

        // Taille et position du monde
        sf::Vector2f m_position;
        sf::Vector2f m_taille;

    private:
};

#endif // MONDE_H
