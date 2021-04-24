#include "Map.h"

#include "../Util/Config.h"

constexpr int COLOUR_RECOGNISE_THRESHOLD = 220;

Map::Map(const Config& config)
    : m_pConfig(&config)
{
    m_mapTexture.loadFromImage(config.image);
    m_sprite.setTexture(&m_mapTexture);
    m_sprite.setSize({(float)config.width, (float)config.height});
}

void Map::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

bool Map::isWaterAt(unsigned x, unsigned y) const
{
    return m_pConfig->image.getPixel(x, y).b >= COLOUR_RECOGNISE_THRESHOLD;
}

bool Map::isLandAt(unsigned x, unsigned y) const
{
    return m_pConfig->image.getPixel(x, y).g >= COLOUR_RECOGNISE_THRESHOLD;
}
