#include "World.h"

World::World()
{
    m_worldTexture.loadFromFile("res/world_map.png");
    m_world.setTexture  (&m_worldTexture);
    m_world.setSize     ({1280, 720});

    m_worldImage.loadFromFile("res/world_map.png");
    m_worldTexture.loadFromImage(m_worldImage);
}

void World::update()
{

}

void World::draw(sf::RenderWindow& window)
{
    window.draw(m_world);
}
