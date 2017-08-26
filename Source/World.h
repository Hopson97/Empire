#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Person.h"

struct Colony
{
    uint8_t id;
    sf::Color colour;
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
        void initColonyTypes();
        void placeColonies();

        sf::RectangleShape  m_world;
        sf::Texture         m_worldTexture;
        sf::Image           m_worldImage;

        std::vector<Person> m_people;
        std::array<Colony, 10> m_colonies;
};

#endif // WORLD_H_INCLUDED
