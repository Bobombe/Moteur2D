#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "mouselistener.h"
#include "ketboardlistener.h"
#include "updatable.h"
#include "animatedsprite.h"
#include "television.h"
#include "connecteur.h"

#include <SFML/Graphics.hpp>


class Personnage : public KeyboardListener, public AnimatedSprite//, public MouseListener
{
    public:
        enum Action
        {
            Arret,
            Saut,
            Courir

        };
        enum Torche
        {
            Etteinte=0,
            TorcheRouge=1,
            TorcheVerte=2,
            TorcheBleue=3
        };

        Personnage(Television& tele);
        virtual ~Personnage();
/*
        virtual void buttonPressed(sf::Event::MouseButtonEvent mbe);
        virtual void buttonReleased(sf::Event::MouseButtonEvent mbe){}
        virtual void mouseMoved(sf::Event::MouseMoveEvent mme){}
        virtual void mouseWheel(sf::Event::MouseWheelEvent mwe);
//*/
        virtual void update(float seconds);

        virtual void keyPressed(sf::Keyboard::Key k);
        virtual void keyReleased(sf::Keyboard::Key k);

        void setAuSol(float posY)
        {
            m_auSol = posY;
        }

        void changeTorche(int couleur);

        int getTorche()
        {
            return m_torche;
        }
        void setConnecteur(int id, int couleur)
        {
            m_idConnecteur = id;
            m_couleurConnecteur = couleur;
        }
        void unsetConnecteur()
        {
            m_idConnecteur = -1;
            m_couleurConnecteur = -1;
        }

        void setFlamme(int couleur)
        {
            m_flamme = couleur;
        }
        void unsetFlamme()
        {
            m_flamme = -1;
        }


    protected:

        virtual void checkCollision(float seconds, sf::Vector2f oldPos);
        void init();

        Television & m_tele;

        // Booléens de mouvements
        bool m_droite;
        bool m_gauche;
        // pour sauts
        bool m_jump;
        float m_auSol;

        // Pour affichage
        bool m_orienteDroite;
        Action m_currentAction;

        //Pour la torche
        Torche m_torche;
        int m_couleurTorche;// renseigne la couleur de torche possible

        //Connecteur
        int m_idConnecteur;
        int m_couleurConnecteur;

        // Flammes
        int m_flamme; //-1 si aucune ; Sinon 1,2 ou 3 selon la couleur

        // Pour reset
        sf::Vector2f m_posDepart;

    private:
};

#endif // PERSONNAGE_H
