#include "Application.h"

#include <iostream>
#include <ctime>

#include "Util/Common.h"

Application::Application(const Config& config)
:   m_window    ({config.width, config.height}, "Empire")
,   m_world     (config)
,   m_pConfig   (&config)
{
    m_pixelBuffer.create(m_pConfig->width, m_pConfig->height);
    updateImage();

    m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
    m_pixelSurface.setSize({(float)config.width, (float)config.height});
    m_pixelSurface.setTexture(&m_pixelSurfaceTex);

    m_GUIFont.loadFromFile("Res/arial.ttf");
    m_GUIText.setFont(m_GUIFont);
    m_GUIText.setCharacterSize(15);

    m_button.setSize({32, 32});
    m_button.setPosition(8, 8);

    m_buttonTexture.loadFromFile("Res/sigma.png");
    m_button.setTexture(&m_buttonTexture);
}

void Application::run()
{
    unsigned year = 0;
    sf::Clock c;

    while (m_window.isOpen())
    {
        auto ti = c.restart().asSeconds();
        m_GUIText.setString("Years: " + std::to_string(year++));
        m_window.clear();

        update();

        m_world.draw(m_window);

        m_window.draw(m_pixelSurface);

        auto pos = sf::Mouse::getPosition(m_window);
        if (m_button.getGlobalBounds().contains(pos.x, pos.y))
        {
            m_world.drawText(m_window);
            m_window.draw(m_GUIText);
        }
        else
        {
            m_window.draw(m_button);
        }

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
        else if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::P)
            {
                makeImage();
            }
        }
    }
}

//Takes the pixels that makes up the people, and save it to an image
void Application::makeImage()
{
    static int imageCount = 0;
    std::cout << "Saving image... Please hold...\n";
    std::string fileName = "Screenshots/Screenshot" + std::to_string(imageCount++) + ".png";

    if (m_pixelBuffer.saveToFile(fileName))
    {
        std::cout << "Saved, to file " << fileName << "! Be aware, future sessions WILL OVERRIDE these images\n\n";
    }
    else
    {
        std::cout << "Failed to save!\n\n";
    }
}

void Application::updateImage()
{
    cellForEach(*m_pConfig, [&](unsigned x, unsigned y)
    {
        m_pixelBuffer.setPixel(x, y, m_world.getColorAt(x, y));
    });
}

void Application::update()
{
    m_world.update();
    updateImage();

    m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
}


