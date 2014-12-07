#ifndef FIXEDSPRITE_H
#define FIXEDSPRITE_H

#include <SFML/Graphics.hpp>
#include "iostream"
#include <map>

class FixedSprite
{
    struct animationTexture
    {
        int first;
        int last;
    };
    public:
        // CONSTRUCTEURS
        FixedSprite(bool addToFixedSpriteList = true);
        FixedSprite(const std::string& imagePath, bool addToFixedSpriteList = true);
        FixedSprite(const sf::Vector2f& pos, const std::string& imagePath = "", bool addToFixedSpriteList = true);
        // Constructeur avec texture animée
        FixedSprite(const std::string& texturePath, const sf::Vector2f& size, int nbLignes, int nbColumns, bool addToFixedSpriteList = true);

        // DESTRUCTEUR
        virtual ~FixedSprite();

        // METHODES
        virtual bool isCollidablePoint(sf::Vector2f pointInGlobalCoordinate);
        virtual void jesuis();
        void addAnimation(std::string name, int firstImageId, int lastImageId);
        void updateTexture(float s);

        // SETTERS
        void setSprite(const std::string& imagePath);
        void setPosition(const sf::Vector2f &pos);
        void setPosition(float x, float y);
        void setRotation(float degree);
        void setScale(float scale);
        void setAnimation(std::string name);
        void setFps(int fps);

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

        // pour la texture annimée
        int m_columns;
        int m_lignes;
        std::map<std::string, struct animationTexture> m_animations;
        std::string m_currentAnimation;
        int currentTextureId;
        float m_time;
        sf::Vector2f m_sizeSprite;
        int m_fps;

    private:
};

#endif // FIXEDSPRITE_H
