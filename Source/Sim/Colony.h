#ifndef COLONY_H_INCLUDED
#define COLONY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <array>

struct Colony
{
    uint8_t     id;
    sf::Color   colour;

};

struct ColonyStatistics
{
    uint16_t    highestStrength = 0;
    int strength    = 0;
    int members     = 0;
    sf::Text text;
    std::string name;
};

class ColonyCreator
{
    public:
        ColonyCreator(const sf::Image& image, int numColonies);

        std::vector<sf::Vector2i>  createColonyLocations(unsigned mapWidth, unsigned mapHeight) const;
        std::vector<Colony>        createColonyStats() const;

    private:
        const sf::Image* m_pImage;
        int m_numColonies;

        std::vector<sf::Color> m_colours;

};

#endif // COLONY_H_INCLUDED
