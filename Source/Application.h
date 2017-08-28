#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <mutex>

#include "Sim/World.h"
#include "Util/NonCopyable.h"
#include "Util/NonMoveable.h"

struct Config;

class Application : public NonCopyable, public NonMovable
{
    public:
        Application(const Config& config);
        ~Application();

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

        const Config* m_pConfig;

        sf::Image           m_pixelBuffer;
        sf::Texture         m_pixelSurfaceTex;
        sf::RectangleShape  m_pixelSurface;

        sf::Text m_GUIText;
        sf::RectangleShape m_button;

        sf::View m_view;

        std::vector<std::thread> m_threads;
        std::mutex m_worldMutex;
};

#endif // APPLICATION_H_INCLUDED
