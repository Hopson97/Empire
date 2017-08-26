#include "Application.h"

Application::Application()
:   m_window    ({WIDTH, HEIGHT}, "Empire")
,   m_pixels    (WIDTH * HEIGHT)
{
    m_window.setFramerateLimit(60);
    cellForEach([&](int x, int y)
    {
        auto& p     = m_pixels[getIndex(x, y)];
        p.position  = {(float)x, (float)y};
        p.color     = m_world.getColorAt(x, y);
    });
}

void Application::run()
{
    while (m_window.isOpen())
    {
        m_window.clear();

        update();

        m_world.draw(m_window);
        m_window.draw(m_pixels.data(), m_pixels.size(), sf::Points);

        m_window.display();
        pollEvents();
        m_frameCount++;
    }
}


void Application::pollEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            m_window.close();
        }
    }
}

void Application::setCellColour(int x, int y, sf::Uint8 colour)
{

}

void Application::update()
{

}
