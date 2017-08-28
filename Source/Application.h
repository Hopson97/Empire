#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

#include "World.h"
#include "Common.h"
#include "Config.h"

class Application
{
    public:
        Application(const Config& config);

        void run();

    private:
        void makeImage();
        void updateImage();

        void pollEvents();
        void update();

        sf::RenderWindow m_window;

        World m_world;

        int m_frameCount = 0;

        const Config* m_pConfig;

        sf::Image           m_pixelBuffer;
        sf::Texture         m_pixelSurfaceTex;
        sf::RectangleShape  m_pixelSurface;

        sf::Text m_GUIText;
        sf::Font m_GUIFont;

        sf::RectangleShape m_button;
        sf::Texture        m_buttonTexture;
};

#endif // APPLICATION_H_INCLUDED
