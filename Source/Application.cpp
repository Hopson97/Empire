#include "Application.h"

#include <iostream>
#include <ctime>

#include "Util/Common.h"

#include "ResourceManager/ResourceHolder.h"

Application::Application(const Config& config)
:   m_window    ({config.width, config.height}, "Empire")
,   m_world     (config)
,   m_pConfig   (&config)
{
    m_window.setFramerateLimit(100);

    m_view.setCenter({(float)config.width / 2, (float)config.height / 2});
    m_view.setSize  ({(float)config.width,     (float)config.height});


    m_pixelBuffer.create(m_pConfig->width, m_pConfig->height);
    updateImage();

    m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
    m_pixelSurface.setSize({(float)config.width, (float)config.height});
    m_pixelSurface.setTexture(&m_pixelSurfaceTex);

    m_GUIText.setFont(ResourceHolder::get().fonts.get("arial"));
    m_GUIText.setCharacterSize(15);

    m_button.setSize({32, 32});
    m_button.setPosition(8, 8);

    m_button.setTexture(&ResourceHolder::get().textures.get("sigma"));
}

void Application::run()
{
    sf::Clock deltaClock;
    unsigned year = 0;
    while (m_window.isOpen())
    {
        m_GUIText.setString("Years: " + std::to_string(year++));
        m_window.clear();

        m_fpsCounter.update();

        input   (deltaClock.restart().asSeconds());
        update  ();

        m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
        render  ();

        m_window.display();

        pollEvents();
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
            if (e.key.code == sf::Keyboard::Up)
            {
                m_view.zoom(0.99);
            }
            if (e.key.code == sf::Keyboard::Down)
            {
                m_view.zoom(1.01);
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

void Application::input(float dt)
{
    float speed = 100;
    sf::Vector2f change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        change.y -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        change.x -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change.x += speed;
    }

    m_view.move(change * dt);
}

void Application::update()
{
    m_world.update();
    updateImage();
}

void Application::render()
{
    m_window.setView(m_view);
    m_world.draw(m_window);
    m_window.draw(m_pixelSurface);
    m_window.setView(m_window.getDefaultView());

    auto pos = sf::Mouse::getPosition(m_window);
    if (m_button.getGlobalBounds().contains(pos.x, pos.y))
    {
        m_world.drawText(m_window);
        m_window.draw(m_GUIText);
        m_fpsCounter.draw(m_window);
    }
    else
    {
        m_window.draw(m_button);
    }
}

