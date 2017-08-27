#ifndef COLONY_H_INCLUDED
#define COLONY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <array>

constexpr int NUM_COLONIES = 10;

struct Colony
{
    uint8_t     id;
    uint16_t    startStrLow;
    uint16_t    startStrHigh;
    sf::Color   colour;
};

struct ColonyStatistics
{
    int strength    = 0;
    int members     = 0;
    sf::Text text;
    std::string name;
};

class ColonyCreator
{
    public:
        ColonyCreator(const sf::Image& image);

        std::array<sf::Vector2i, NUM_COLONIES>  createColonyLocations(unsigned mapWidth, unsigned mapHeight) const;
        std::array<Colony, NUM_COLONIES>        createColonyStats() const;

    private:
        const sf::Image* m_pImage;

        std::vector<sf::Color> m_colours;

};

#endif // COLONY_H_INCLUDED
