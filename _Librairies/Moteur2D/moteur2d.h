#ifndef MOTEUR2D_H
#define MOTEUR2D_H

#include <map>
#include <vector>

#include <SFML/Graphics.hpp>
#include "updatable.h"

#include "fixedsprite.h"
#include "animatedsprite.h"
#include "mouselistener.h"
#include "ketboardlistener.h"
#include "gravity.h"
#include "view.h"
#include "concretebackground.h"
#include "monde.h"

class Moteur2D
{
    public:
        static Moteur2D* getInstance();

  /////////////////////////////////////////////////////
 ///////////          METHODES             ///////////
/////////////////////////////////////////////////////
        void init(int width=800, int height=600, std::string windowName ="Youpi");
        void run();
        void updateView();

  /////////////////////////////////////////////////////
 ///////////           ADDERS              ///////////
/////////////////////////////////////////////////////
        int addPreDrawable(sf::Sprite* s);
        int addDrawable(sf::Sprite *s);
        int addPostDrawable(sf::Sprite* s);

        void addFixedSprite(FixedSprite* fs);
        void addAnimatedSprite(AnimatedSprite* as);

        int addConcreteBackground(ConcreteBackground* cb);
        int addWorld(Monde *w);

        int addKeyboardListener(KeyboardListener* kl);
        int addMouseListener(MouseListener* ml);

        int addPreUpdate(Updatable *u);
        int addPostUpdate(Updatable *u);

  /////////////////////////////////////////////////////
 ///////////          DELETERS             ///////////
/////////////////////////////////////////////////////
        void deletePreDrawable(int index);
        void deleteDrawable(int index);
        void deletePostDrawable(int index);

        void deleteFixedSprite(FixedSprite*fs);
        void deleteAnimatedSprite(AnimatedSprite*as);

        void deleteConcreteBackground(int index);
        void deleteWorld(int index);

        void deleteKeyboardListener(int index);
        void deleteMouseListener(int index);

        void deletePreUpdate(int index);
        void deletePostUpdate(int index);

  /////////////////////////////////////////////////////
 ///////////           GETTERS             ///////////
/////////////////////////////////////////////////////
        sf::Texture* getTexture(const std::string& imagePath);

        sf::RenderWindow & getWindow();
        View * getView();

        const std::map <int, KeyboardListener*>& getKeyboardListeners();
        const std::map <int, MouseListener*>& getMouseListeners();

        const std::vector <FixedSprite*>& getFixedSprites();
        const std::vector <AnimatedSprite*>& getAnimatedSprites();

        const std::map <int, ConcreteBackground*>& getConcreteBackgrounds();

        sf::Time getTime();

    protected:
        Moteur2D();
        virtual ~Moteur2D();

        static Moteur2D * m_instance;

        sf::RenderWindow *m_window;
        View m_view;

        std::map<std::string, sf::Texture> m_textures;
        //std::vector <Updatable*> m_updates;


        // First called by eventmanager
        std::map <int, KeyboardListener*> m_keyboardListeners;
        int m_keyboardListenersId;
        std::map <int, MouseListener*> m_mouseListeners;
        int m_mouseListenersId;

        //Then make the Updates needed before updating positions of objects (external forcies like gravity)
        std::map <int, Updatable*> m_preUpdates;
        int m_preUpdateId;

        //then update animated object according to interactions with other objects (collisions)
        std::vector <AnimatedSprite*> m_animatedSprites;
        std::vector <FixedSprite*> m_fixedSprites;

        //Then make the Updates needed after updating positions of objects (I don't know what yet)
        //std::vector <Updatable*> m_postUpdates;
        std::map <int, Updatable*> m_postUpdates;
        int m_postUpdateId;

        /*/-------- And to finish draw all --------\\

        // TO DO : Pour m_preDraw et m_postDraw : passer en map pouvant avoir plusieurs index égaux représentant la profondeur
        // Dessinables avant perso et autres//*/
        //std::vector <sf::Drawable*> m_preDraw;
        std::map <int, sf::Sprite*> m_preDraw;
        int m_preDrawablesIndex;

        // Background tengible
        std::map <int, ConcreteBackground*> m_concreteBackgrounds;
        int m_concreteBackgroundsIndex;

        // On en fait tout un monde
        std::map <int, Monde*> m_worlds;
        int m_worldsIndex;

        // Dessins au niveau du perso
        std::map <int, sf::Sprite*> m_drawables;
        int m_drawablesIndex;

        // Dessinables après perso et autres
        std::map <int, sf::Sprite*> m_postDraw;
        int m_postDrawablesIndex;

        sf::Clock m_clock;
        sf::Time m_t;

    private:
};

#endif // MOTEUR2D_H
