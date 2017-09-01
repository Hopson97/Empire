#ifndef COLONY_H_INCLUDED
#define COLONY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <array>

struct Config;
class  Map;

struct Colony
{
    int         id;
    sf::Color   colour;

    unsigned strLow;
    unsigned strHigh;
};

class ColonyCreator
{
    public:
        ColonyCreator(int numColonies);

        std::vector<sf::Vector2i>  createColonyLocations(const Config& config, const Map& map) const;
        std::vector<Colony>        createColonyStats() const;

    private:
        int m_numColonies;

        std::vector<sf::Color> m_colours;

};

#endif // COLONY_H_INCLUDED
