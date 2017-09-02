#include "Colony.h"

#include <fstream>
#include <iostream>

#include "../Native/Native.h"
#include "../Util/Random.h"
#include "../Util/Config.h"

#include "Map.h"

ColonyCreator::ColonyCreator(int colonies)
:   m_numColonies   (colonies)
{
    std::ifstream inFile("colours.txt");
    if (!inFile.is_open())
    {
        std::cout << TextColour::Red << "Unable to open colours.txt\n\n" << TextColour::Default;
    }
    sf::Color colour;

    int r, g, b;
    while (inFile >> r >> g >> b)
    {
        sf::Uint8 red   = (sf::Uint8)r;
        sf::Uint8 green = (sf::Uint8)g;
        sf::Uint8 blue  = (sf::Uint8)b;

        m_colours.push_back({red, green, blue});
    }
}

std::vector<sf::Vector2i> ColonyCreator::createColonyLocations(const Config& config, const Map& map) const
{
    std::vector<sf::Vector2i> locations(m_numColonies);

    //skip over colony 0
    for (int i = 1; i < m_numColonies; i++)
    {
        int x, y;
        //Loops until land is found
        while (true)
        {
            x = Random::get().intInRange(0, config.width);
            y = Random::get().intInRange(0, config.height);
            if (map.isLandAt(x, y))
            {
                locations[i] = {x, y};
                break;
            }
        }
    }

    return locations;
}

std::vector<Colony> ColonyCreator::createColonyStats() const
{
    std::vector<Colony> colonies(m_numColonies);

    //Colony 0 is reserved for the dead
    colonies[0].colour  = {0, 0, 0, 0};
    colonies[0].id      = 0;

    //skip over colony 0
    for (int i = 1; i < m_numColonies; i++)
    {
        auto& col = colonies[i];

        col.strLow  = Random::get().intInRange(400, 410);
        col.strHigh = Random::get().intInRange(645, 655);

        if (i > (int)m_colours.size() - 1)
        {
            sf::Uint8 r = Random::get().intInRange(0, 255);
            sf::Uint8 g = Random::get().intInRange(0, 255);
            sf::Uint8 b = Random::get().intInRange(0, 255);
            col.colour   = {r, g, b};
        }
        else
        {
            colonies[i].colour = m_colours[i];
        }
        colonies[i].id = i;
    }

    return colonies;
}

