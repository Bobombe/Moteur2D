#ifndef FIXEDSPRITE_H
#define FIXEDSPRITE_H

#include <SFML/Graphics.hpp>
#include "iostream"

class FixedSprite
{
    public:
        // CONSTRUCTEURS
        FixedSprite(bool addToFixedSpriteList = true);
        FixedSprite(const std::string& imagePath, bool addToFixedSpriteList = true);
        FixedSprite(const sf::Vector2f& pos, const std::string& imagePath = "", bool addToFixedSpriteList = true);

        // DESTRUCTEUR
        virtual ~FixedSprite();

        // METHODES
        virtual bool isCollidablePoint(sf::Vector2f pointInGlobalCoordinate);
        virtual void jesuis();

        // SETTERS
        void setSprite(const std::string& imagePath);
        void setPosition(const sf::Vector2f &pos);
        void setRotation(float degree);
        void setScale(float scale);

        //GETTERS
        sf::Vector2f getPosition();
        sf::FloatRect getBox();
        sf::Sprite* getSprite();
        sf::Vector2f getSize();
        float getWidth();
        float getHeight();
        // OPERATORS
        bool operator !=(const FixedSprite &fs) const
        {
            return fs.m_indexOfSprite != m_indexOfSprite;
        }
    protected:
        sf::FloatRect m_bBox;

        sf::Sprite * m_sprite;
        int m_indexOfSprite;
        sf::Image m_image;

        //Mémorise la taille de l'image
        sf::Vector2f m_size;
    private:
};

#endif // FIXEDSPRITE_H
