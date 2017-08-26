#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Person.h"

class World
{
    public:
        World();

        void update ();
        void draw   (sf::RenderWindow& window);

    private:
        sf::RectangleShape  m_world;
        sf::Texture         m_worldTexture;
        sf::Image           m_worldImage;

        std::vector<Person> m_people;
};

#endif // WORLD_H_INCLUDED
