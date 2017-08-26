#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Person.h"

constexpr int NUM_COLONIES = 10;

struct Colony
{
    uint8_t id;
    sf::Color colour;
};

struct ColonyCount
{
    int members = 0;
    sf::Text text;
    std::string name;
};

class World
{
    public:
        World();

        void update ();
        void draw   (sf::RenderWindow& window);

        const sf::Color& getColorAt(unsigned x, unsigned y);

    private:
        void createColonies();
        void initText();

        sf::RectangleShape  m_world;
        sf::Texture         m_worldTexture;
        sf::Image           m_worldImage;
        sf::Font            m_counterFont;

        std::vector<Person> m_people;
        std::array<Colony,      NUM_COLONIES> m_colonies;
        std::array<ColonyCount, NUM_COLONIES> m_colonyCount;

};

#endif // WORLD_H_INCLUDED
