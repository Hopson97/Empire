#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <memory>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Biome.h"

#include "../Util/Grid.h"

struct Config;

class Map
{
    public:
        typedef std::shared_ptr<Biome::Base> BiomePtr;

        Map(const Config& config);

        void draw(sf::RenderWindow& window) const;

        sf::Color getPixelAt(unsigned x, unsigned y) const;
        const BiomePtr& getBiomeAt(unsigned x, unsigned y) const;
        
    private:
        sf::Texture         m_mapTexture;
        sf::RectangleShape  m_sprite;
        Grid<BiomePtr>      m_biomes;

        const Config* m_pConfig = nullptr;

};

#endif // MAP_H_INCLUDED
