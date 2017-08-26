#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

#include "World.h"

constexpr unsigned WIDTH = 1280;
constexpr unsigned HEIGHT = 720;

class Application
{
    public:
        Application();

        void run();

    private:
        template<typename F>
        void cellForEach(F f)
        {
            for (unsigned y = 0; y < HEIGHT; y++)
            {
                for (unsigned x = 0; x < WIDTH; x++)
                {
                    f(x, y);
                }
            }
        }


        int getIndex(int x, int y);

        void pollEvents();
        void setCellColour(int x, int y, sf::Uint8 colour);
        void update();

        sf::RenderWindow m_window;
        std::vector<sf::Vertex> m_pixels;

        World m_world;

        int m_frameCount = 0;
};

#endif // APPLICATION_H_INCLUDED
