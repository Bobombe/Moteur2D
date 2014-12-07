#ifndef FLAMME_H
#define FLAMME_H

#include <SFML/Graphics.hpp>

class Flamme
{
    public:
        Flamme(int couleur, int posX, int posY);
        virtual ~Flamme();

        sf::FloatRect getBox()
        {
            return m_sprite.getGlobalBounds();
        }

        sf::Sprite m_sprite;
        int m_couleur;
    protected:
    private:
};
#endif // FLAMME_H
