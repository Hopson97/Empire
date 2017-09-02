#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "Person.h"
#include "Colony.h"
#include "../Util/Grid.h"

struct Config;

class World
{
    public:
        World(const Config& config);

        void update     (sf::Image& image);
        void draw       (sf::RenderWindow& window) const;
        void drawText   (sf::RenderWindow& window);

        const sf::Color& getColorAt(unsigned x, unsigned y) const;

    private:
        bool isGrass    (unsigned x, unsigned y)    const;
        bool isWater    (unsigned x, unsigned y)    const;
        
        sf::Color getPixelAt(unsigned x, unsigned y) const;

        void createColonies();
        void initText();

        sf::RectangleShape  m_world;
        sf::Texture         m_worldTexture;

        Grid<Person>                    m_people;
        std::vector<Colony>             m_colonies;
        std::vector<ColonyStatistics>   m_colonyStats;

        const Config* m_pConfig;

};

#endif // WORLD_H_INCLUDED
