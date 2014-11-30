
#include "moteur2d.h"
#include <stdexcept>
#include <iostream>

#include "eventmanager.h"

Moteur2D * Moteur2D::m_instance = 0;

Moteur2D * Moteur2D::getInstance()
{
    if (m_instance == 0)
    {
        m_instance = new Moteur2D();
    }
    return m_instance;
}

Moteur2D::Moteur2D()
{
    //ctor
}

Moteur2D::~Moteur2D()
{
    //dtor
    // TO DO : revoir le destructeur
    if(m_instance)
        delete m_instance;

    delete m_window;
    // TO DO : Détruire le contenu des vectors
}


  /////////////////////////////////////////////////////
 ///////////          METHODES             ///////////
/////////////////////////////////////////////////////

void Moteur2D::init(int width, int height, std::string windowName)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), windowName, sf::Style::Default, settings);

    sf::View v = m_window->getDefaultView();
    m_view.setSize(v.getSize());
    m_view.setCenter(v.getCenter());
    updateView();

        // Init des Id
    m_keyboardListenersId = 0;
    m_mouseListenersId = 0;

    m_preUpdateId = 0;
    m_postUpdateId = 0;

    m_preDrawablesIndex = 0;
    m_drawablesIndex = 0;
    m_postDrawablesIndex = 0;

    m_concreteBackgroundsIndex = 0;
    m_worldsIndex = 0;
}

void Moteur2D::run()
{

    EventManager em;
    m_t = m_clock.getElapsedTime();
    sf::Time t2;
    float s;
    m_window->setVerticalSyncEnabled(true);
    //m_window->setFramerateLimit(60);

    while(m_window->isOpen())
    {
        // On efface la fenètre dès le début pour permettre aux Updatables de déssiner
        m_window->clear();// efface la fenètre

        // TO DO : Relacher le proc
        //Attente
        // Attente active
        do
        {
            t2 = m_clock.getElapsedTime();
            s = (t2-m_t).asSeconds() ;
        }while (s<1/60.);
        /*/

        Attente non active, mais ne régularise pas le 60 fps, sleep n'est pas fiable
        sf::Time t;
        t2 = m_clock.getElapsedTime();
        t = (t2-m_t);
        t = sf::milliseconds(16)-t;
        std::cout << "t = "<< t.asMilliseconds();
        if (t.asMilliseconds()>0)
            sf::sleep(t);
        else
            std::cout << " retard "<<std::endl;

        std::cout  << "attente = " << (-t2+m_clock.getElapsedTime()).asMilliseconds();
        t2 = m_clock.getElapsedTime();
        s = (t2-m_t).asSeconds() ;
        std::cout << ", fps = " << 1./s << std::endl;
        //*/

        // First called by eventmanager
        em.eventLoop(*m_window);

        /*/Then make the Updates needed before updating positions of objects (external forces like gravity)//*/

        for (std::map<int,Updatable*>::iterator it=m_preUpdates.begin(); it!=m_preUpdates.end(); ++it)
        {
            it->second->update(s);
        }

        //then update animated object according to interactions with other objects (collisions)
        for (unsigned int i =0; i<m_animatedSprites.size(); i++)
        {
            m_animatedSprites.at(i)->update(s);
        }

        //Then make the Updates needed after updating positions of objects (I don't know what yet)
        for (std::map<int,Updatable*>::iterator it=m_postUpdates.begin(); it!=m_postUpdates.end(); ++it)
        {
            it->second->update(s);
        }

        //And to finish draw all
        // Dessine tous les objets dessinables
        for (std::map<int,sf::Sprite*>::iterator it=m_preDraw.begin(); it!=m_preDraw.end(); ++it)
        {
            m_window->draw(*(it->second));
        }
        for (std::map<int,ConcreteBackground*>::iterator it=m_concreteBackgrounds.begin(); it!=m_concreteBackgrounds.end(); ++it)
        {
            sf::Sprite* sprite= (it->second)->getSprite();
            if (sprite)
                m_window->draw(*sprite);
        }

        for (std::map<int,sf::Sprite*>::iterator it=m_drawables.begin(); it!=m_drawables.end(); ++it)
        {
            m_window->draw(*(it->second));
        }

        for (std::map<int,sf::Sprite*>::iterator it=m_postDraw.begin(); it!=m_postDraw.end(); ++it)
        {
            m_window->draw(*(it->second));
        }

        m_window->display();// Affiche

        //MaJ temps
        m_t = t2;

    }
}

void Moteur2D::updateView()
{
    m_window->setView(m_view);
}


  /////////////////////////////////////////////////////
 ///////////           ADDERS              ///////////
/////////////////////////////////////////////////////

int Moteur2D::addPreDrawable(sf::Sprite* s)
{
    m_preDrawablesIndex++;
    m_preDraw[m_preDrawablesIndex] = s;
    return m_preDrawablesIndex;
}
int Moteur2D::addDrawable(sf::Sprite *s)
{
    m_drawablesIndex++;
    m_drawables[m_drawablesIndex] = s;
    return m_drawablesIndex;
}
int Moteur2D::addPostDrawable(sf::Sprite* s)
{
    m_postDrawablesIndex++;
    m_postDraw[m_postDrawablesIndex] = s;
    return m_postDrawablesIndex;
}


void Moteur2D::addFixedSprite(FixedSprite* fs)
{
    m_fixedSprites.push_back(fs);
}
void Moteur2D::addAnimatedSprite(AnimatedSprite* as)
{
    m_animatedSprites.push_back(as);
}


int Moteur2D::addConcreteBackground(ConcreteBackground* cb)
{
    m_concreteBackgroundsIndex++;
    m_concreteBackgrounds[m_concreteBackgroundsIndex] = cb;
    return m_concreteBackgroundsIndex;
}
int Moteur2D::addWorld(Monde *w)
{
    m_worldsIndex++;
    m_worlds[m_worldsIndex] = w;
    return m_worldsIndex;
}


int Moteur2D::addKeyboardListener(KeyboardListener* kl)
{
    ++m_keyboardListenersId;
    m_keyboardListeners[m_keyboardListenersId]=kl;
    return m_keyboardListenersId;
}
int Moteur2D::addMouseListener(MouseListener* ml)
{
    ++m_mouseListenersId;
    m_mouseListeners[m_mouseListenersId]=ml;
    return m_mouseListenersId;
}


int Moteur2D::addPreUpdate(Updatable *u)
{
    ++m_preUpdateId;
    m_preUpdates[m_preUpdateId]=u;
    return m_preUpdateId;
}
int Moteur2D::addPostUpdate(Updatable *u)
{
    ++m_postUpdateId;
    m_postUpdates[m_postUpdateId]=u;
    return m_postUpdateId;
}

  /////////////////////////////////////////////////////
 ///////////          DELETERS             ///////////
/////////////////////////////////////////////////////

void Moteur2D::deletePreDrawable(int index)
{
    m_preDraw.erase(index);
}
void Moteur2D::deleteDrawable(int index)
{
    m_drawables.erase(index);
}
void Moteur2D::deletePostDrawable(int index)
{
    m_postDraw.erase(index);
}


void Moteur2D::deleteFixedSprite(FixedSprite*fs)
{
    for (unsigned int i = 0; i < m_fixedSprites.size(); i++)
    {
        if (fs==m_fixedSprites.at(i))
        {
            m_fixedSprites.erase(m_fixedSprites.begin()+i);
        }
    }
}
void Moteur2D::deleteAnimatedSprite(AnimatedSprite*as)
{
    for (unsigned int i = 0; i < m_animatedSprites.size(); i++)
    {
        if (as==m_animatedSprites.at(i))
        {
            m_animatedSprites.erase(m_animatedSprites.begin()+i);
        }
    }
}


void Moteur2D::deleteConcreteBackground(int index)
{
    m_concreteBackgrounds.erase(index);
}
void Moteur2D::deleteWorld(int index)
{
    m_worlds.erase(index);
}


void Moteur2D::deleteKeyboardListener(int index)
{
    m_keyboardListeners.erase(index);
}
void Moteur2D::deleteMouseListener(int index)
{
    m_mouseListeners.erase(index);
}


void Moteur2D::deletePreUpdate(int index)
{
    m_preUpdates.erase(index);
}
void Moteur2D::deletePostUpdate(int index)
{

    m_postUpdates.erase(index);
}



  /////////////////////////////////////////////////////
 ///////////           GETTERS             ///////////
/////////////////////////////////////////////////////
// Permet l'accès aux textures, si la texture est inexistante cette methode la créera.
sf::Texture* Moteur2D::getTexture(const std::string& imagePath)
{
    try
    {
        return &m_textures.at(imagePath);
    }
    catch (const std::out_of_range& oor)
    {
        // Texture inéxistante, je la charge
        sf::Texture t;
        t.loadFromFile(imagePath);
        m_textures.insert(std::pair<std::string, sf::Texture>(imagePath, t));
    }
    try
    {
        return &m_textures.at(imagePath);
    }
    catch (const std::out_of_range& oor)
    {
        // problem !
        std::cerr << "Problème d'ajout de Texture" << std::endl;
        return 0;
    }
}

View * Moteur2D::getView()
{
    return &m_view;
}
sf::RenderWindow & Moteur2D::getWindow()
{
    return *m_window;
}

const std::map <int, KeyboardListener*>& Moteur2D::getKeyboardListeners()
{
    return m_keyboardListeners;
}
const std::map <int, MouseListener*>& Moteur2D::getMouseListeners()
{
    return m_mouseListeners;
}

const std::vector <FixedSprite*>& Moteur2D::getFixedSprites()
{
    return m_fixedSprites;
}
const std::vector <AnimatedSprite*>& Moteur2D::getAnimatedSprites()
{
    return m_animatedSprites;
}
const std::map <int, ConcreteBackground*>& Moteur2D::getConcreteBackgrounds()
{
    return m_concreteBackgrounds;
}
sf::Time Moteur2D::getTime()
{
    return m_clock.getElapsedTime();
}





