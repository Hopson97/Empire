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
        void pollEvents();
        void update();

        sf::RenderWindow m_window;
        std::vector<sf::Vertex> m_pixels;

        World m_world;

        int m_frameCount = 0;

        const Config* m_pConfig;
};

#endif // APPLICATION_H_INCLUDED
