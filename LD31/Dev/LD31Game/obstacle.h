#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>


class Obstacle
{
    public:
        Obstacle(std::string couleur, int tX, int tY, int posX, int posY, bool traversableV = false);
        virtual ~Obstacle();

        bool estAPorte(sf::Vector2f pos, float distance);

        sf::FloatRect getBox()
        {
            return m_sprite.getGlobalBounds();
        }

        sf::Sprite m_sprite;
    protected:
        bool m_isTraversableVertical;
    private:
};

#endif // OBSTACLE_H
