#include "FPSCounter.h"

#include "../ResourceManager/ResourceHolder.h"

#include <iostream>

FPSCounter::FPSCounter()
{
    m_text.move(10, 20);
    m_text.setFillColor(sf::Color::White);
    m_text.setFont(ResourceHolder::get().fonts.get("arial"));
    m_text.setCharacterSize(14);
}

void FPSCounter::update()
{
    m_frameCount++;

    if (m_delayTimer.getElapsedTime().asSeconds() > 0.2) {
        m_fps = m_frameCount / m_fpsTimer.restart().asSeconds();
        m_frameCount = 0;
        m_delayTimer.restart();
    }
}

void FPSCounter::draw(sf::RenderTarget& renderer)
{
    m_text.setString("FPS: " + std::to_string((int)m_fps));
    renderer.draw(m_text);
}
