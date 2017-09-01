#include "Map.h"

#include "../Util/Config.h"

Map::Map(const Config& config)
{
    m_mapTexture.loadFromImage(config.image);
    m_sprite.setTexture  (&m_mapTexture);
    m_sprite.setSize     ({(float)config.width,
                          (float)config.height});
}

void Map::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}
