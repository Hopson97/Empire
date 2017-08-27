#include "Application.h"

Application::Application(const Config& config)
:   m_window    ({config.width, config.height}, "Empire", sf::Style::Close)
,   m_pixels    (config.width * config.height)
,   m_world     (config)
,   m_pConfig   (&config)
{
    m_window.setFramerateLimit(100);
    cellForEach(*m_pConfig, [&](int x, int y)
    {
        auto& p     = m_pixels[getIndex(m_pConfig->width, x, y)];
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
        m_world.drawText(m_window);

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

void Application::update()
{
    m_world.update();
    cellForEach(*m_pConfig, [&](unsigned x, unsigned y)
    {
        m_pixels[getIndex(m_pConfig->width, x, y)].color = m_world.getColorAt(x, y);
    });
}
















