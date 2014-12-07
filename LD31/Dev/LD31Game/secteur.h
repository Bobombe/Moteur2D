#ifndef SECTEUR_H
#define SECTEUR_H

#include "obstacle.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Secteur
{
    public:
        Secteur(int px = 0, int py = 0);
        virtual ~Secteur();

        void draw(sf::RenderWindow & window);

        void updateFond();

        void modifieAlimCouleur(int couleur, bool ajout = true);

        void init();

        void ajoutRouge()
        {
            m_nbSourcesRouges++;
        }
        void ajoutVert()
        {
            m_nbSourcesVertes++;
        }
        void ajoutBleu()
        {
            m_nbSourcesBleues++;
        }

        void supRouge()
        {
            m_nbSourcesRouges--;
        }
        void supVert()
        {
            m_nbSourcesVertes--;
        }
        void supBleu()
        {
            m_nbSourcesBleues--;
        }


        bool estAllimenteEnRouge()
        {
            return m_nbSourcesRouges>0;
        }
        bool estAllimenteEnVert()
        {
            return m_nbSourcesVertes>0;
        }
        bool estAllimenteEnBleu()
        {
            return m_nbSourcesBleues>0;
        }

        int getCouleurDeSection();
        int getCouleurAvecTorche();

        void addObstacle(int couleur, int tX, int tY, int posX, int posY, bool traversableV = false);

        std::vector<Obstacle> getCollidables(int couleurTorche, sf::Vector2f posTorche);
    protected:
        // Obstacles du secteur
        std::vector<Obstacle> m_rouges;
        std::vector<Obstacle> m_verts;
        std::vector<Obstacle> m_bleus;
        std::vector<Obstacle> m_jaunes;
        std::vector<Obstacle> m_cyans;
        std::vector<Obstacle> m_magentas;

        // Nombre de Sources de couleurs pour chaque couleur allimentant ce secteur
        int m_nbSourcesRouges;
        int m_nbSourcesVertes;
        int m_nbSourcesBleues;

        // Pour le fond
        sf::Sprite m_fond;
        sf::Texture *m_textureNoire;
        sf::Texture *m_textureRouge;
        sf::Texture *m_textureVerte;
        sf::Texture *m_textureBleue;
        sf::Texture *m_textureJaune;
        sf::Texture *m_textureCyan;
        sf::Texture *m_textureMagenta;
        sf::Texture *m_textureBlanche;

        //Pour la torche
        int m_couleurTorche;
        sf::Vector2f m_posTorche;
    private:
};

#endif // SECTEUR_H
