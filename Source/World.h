#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Person.h"

constexpr int NUM_COLONIES = 12;

struct Config;

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

class World
{
    public:
        World(const Config& config);

        void update     ();
        void draw       (sf::RenderWindow& window) const;
        void drawText   (sf::RenderWindow& window);

        const sf::Color& getColorAt(unsigned x, unsigned y) const;

    private:
        bool isGrass    (unsigned x, unsigned y)    const;
        bool isWater    (unsigned x, unsigned y)    const;

        void createColonies();
        void initText();

        sf::RectangleShape  m_world;
        sf::Texture         m_worldTexture;
        sf::Font            m_statsFont;

        std::vector<Person> m_people;
        std::array<Colony,              NUM_COLONIES> m_colonies;
        std::array<ColonyStatistics,    NUM_COLONIES> m_colonyStats;

        const Config* m_pConfig;

};

#endif // WORLD_H_INCLUDED
