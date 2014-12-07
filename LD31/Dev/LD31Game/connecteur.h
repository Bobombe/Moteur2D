#ifndef CONNECTEUR_H
#define CONNECTEUR_H

#include <SFML/Graphics.hpp>

class Connecteur
{
    public:
        Connecteur(int couleur, int posX, int posY);
        virtual ~Connecteur();

        sf::FloatRect getBox()
        {
            return m_sprite.getGlobalBounds();
        }

        void allumer();
        void etteindre();

        sf::Sprite m_sprite;
        int m_couleur;
        bool m_allumee;
    protected:
    private:
};

#endif // CONNECTEUR_H
