#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

class View : public sf::View
{
    public:
        View();
        virtual ~View();

        // Déplace la vue selon l'offset
        void move(const sf::Vector2f &offset);
        void move(float offsetX, float offsetY);
        void moveWithCharacter(const sf::Vector2f &position);

        // Effectue un zoom centré sur la souris (le pixel sous le curseur ne bouge pas)
        //       et selon le facteur (<1 -> zoom=on voit de plus près)
        void zoomOnMouse(float factor);

        //Retrouve la position du curseur dans les coordonnées du monde depuis les coordonnée de l'écran
        sf::Vector2f getMouseInWorld();
        sf::Vector2f getPosInView(const sf::Vector2f& posInWorld);

        // Retourne le facteur de zoom
        float getZoom();

        void setWorldBoundaries(const sf::FloatRect& wb);


    protected:

        sf::FloatRect m_worldBoundaries;
        bool m_worldBoundariesSet;

    private:
};

#endif // VIEW_H
