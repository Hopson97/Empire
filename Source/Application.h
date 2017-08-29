#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

#include "Sim/World.h"
#include "Util/NonCopyable.h"
#include "Util/NonMoveable.h"
#include "Util/FPSCounter.h"

struct Config;

class Application
{
    public:
        Application(const Config& config);


        void run();

    private:
        void makeImage();
        void updateImage();

        void pollEvents();
        void input  (float dt);
        void update ();
        void render ();

        sf::RenderWindow m_window;

        World m_world;

        FPSCounter m_fpsCounter;

        const Config* m_pConfig;

        sf::Image           m_pixelBuffer;
        sf::Texture         m_pixelSurfaceTex;
        sf::RectangleShape  m_pixelSurface;

        sf::Text m_GUIText;
        sf::RectangleShape m_button;

        sf::View m_view;
};

#endif // APPLICATION_H_INCLUDED
