#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "fixedsprite.h"
#include "updatable.h"


class AnimatedSprite : public Updatable, public FixedSprite //*/ Updatable
{
    public:
        AnimatedSprite();
        AnimatedSprite(const std::string& imagePath, const sf::Vector2f& pos = sf::Vector2f(0, 0), sf::Vector2f vit = sf::Vector2f(0, 0));
        AnimatedSprite(const sf::Vector2f& pos, const std::string& imagePath = "");
        virtual ~AnimatedSprite();


        // GETTERS
        virtual sf::Vector2f getVitesse();

        // SETTERS
        virtual void setVitesse(const sf::Vector2f& v);
        virtual void setVitesse(float vx, float vy);

        virtual void update(float seconds);
        virtual void jesuis()
        {
            std::cout << "AnimatedSprite" << m_indexOfSprite << std::endl;
        }

    protected:
        virtual void checkCollision(float seconds, sf::Vector2f oldPos);
        virtual bool collideWith(const sf::FloatRect &other, const sf::Vector2f & newPos);
        virtual bool collideWith(FixedSprite * fs);
        virtual void applyCollision(FixedSprite * fo, sf::Vector2f oldPos);

        sf::Vector2f m_vit;
    private:
};

#endif // ANIMATEDSPRITE_H
