#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SFML/Graphics.hpp>

struct Config;

class Map
{
    public:
        Map(const Config& config);

        void draw(sf::RenderWindow& window) const;

    private:
        sf::Texture m_mapTexture;
        sf::RectangleShape m_sprite;

        const Config* m_pConfig = nullptr;

};

#endif // MAP_H_INCLUDED
