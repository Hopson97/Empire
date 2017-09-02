#include "Map.h"

#include "../Util/Config.h"

constexpr int COLOUR_RECOGNISE_THRESHOLD = 220;

Map::Map(const Config& config)
:   m_pConfig   (&config)
,	m_biomes	(config.width, config.height)
{
    m_mapTexture.loadFromImage(config.image);
    m_sprite.setTexture  (&m_mapTexture);
    m_sprite.setSize     ({(float)config.width,
                          (float)config.height});
    for(unsigned x = 0; x < config.width; x++) 
    {
    	for(unsigned y = 0; y < config.height; y++) 
    	{
    		m_biomes(x, y) = Biome::getBiomeForColor(getPixelAt(x, y));
    	}
    }
}

void Map::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

sf::Color Map::getPixelAt(unsigned x, unsigned y) const
{
	return m_pConfig->image.getPixel(x, y);
}

const Map::BiomePtr& Map::getBiomeAt(unsigned x, unsigned y) const
{
	return m_biomes(x, y);
}

bool Map::isWaterAt(unsigned x, unsigned y) const
{
    return m_pConfig->image.getPixel(x, y).b >= COLOUR_RECOGNISE_THRESHOLD;
}

bool Map::isLandAt(unsigned x, unsigned y) const
{
    return m_pConfig->image.getPixel(x, y).g >= COLOUR_RECOGNISE_THRESHOLD;
}
