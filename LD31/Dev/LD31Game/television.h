#ifndef TELEVISION_H
#define TELEVISION_H

#include <SFML/Graphics.hpp>
#include "updatable.h"
#include "obstacle.h"
#include "secteur.h"
#include "connecteur.h"
#include "flamme.h"
#include <vector>

class Personnage;

class Television : public Updatable
{
    enum TypeDeCollision
    {
        Aucune,
        SurHaut,
        SurBas,
        SurGauche,
        SurDroite
    };
    public:
        Television(std::string nom);
        virtual ~Television();

        virtual void update(float seconds);

        void collisionPersonnage(Personnage * perso, sf::Vector2f oldPos);

        void collisionEntre(Personnage * perso, sf::Vector2f &oldPos, Obstacle &obst);
        void collisionEntre(Personnage * perso, sf::Vector2f &oldPos, Connecteur &obst, int id);
        void collisionEntre(Personnage * perso, sf::Vector2f &oldPos, Flamme &obst);

        void modifieAlimCouleur(int couleur, int posx, int posy, bool ajout = true);
        void switchConnecteur(int idConnecteur);

        void init();


    protected:
        sf::RenderWindow & m_window;

        sf::Vector2i m_size;

        //sf::Texture* m_gris;
        int m_secteurPerso;

        std::vector<Obstacle> m_obstaclesPermanents;

        // Pour les secteurs
        int m_nbColones;
        int m_nbLignes;
        std::vector<Secteur> m_secteurs;

        // Connecteurs
        std::vector<Connecteur> m_connecteurs;
        // Flammes
        std::vector<Flamme> m_flammes;

        // Suivi de progression
        int m_score;
        sf::Sprite m_conteneur;
        sf::Sprite m_charge;
        sf::Sprite m_fin;
    private:
};

#endif // TELEVISION_H
