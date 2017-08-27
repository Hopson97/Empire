#include "Colony.h"

#include <fstream>
#include <iostream>

#include "Random.h"

ColonyCreator::ColonyCreator(const sf::Image& image)
:   m_pImage    (&image)
{
    std::ifstream inFile("colours.txt");
    if (!inFile.is_open())
    {
        exit(0);
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


std::array<sf::Vector2i, NUM_COLONIES> ColonyCreator::createColonyLocations(unsigned mapWidth, unsigned mapHeight) const
{
    std::array<sf::Vector2i, NUM_COLONIES> locations;

    //skip over colony 0
    for (unsigned i = 1; i < NUM_COLONIES; i++)
    {
        int x, y;
        while (true)
        {
            x = Random::get().intInRange(0, mapWidth);
            y = Random::get().intInRange(0, mapHeight);
            if (m_pImage->getPixel(x, y).g >= 250)
            {
                locations[i] = {x, y};
                break;
            }
        }
    }

    return locations;
}

std::array<Colony, NUM_COLONIES> ColonyCreator::createColonyStats() const
{
    std::array<Colony, NUM_COLONIES> colonies;

    //Colony 0 is reserved for the dead
    colonies[0].colour  = {0, 0, 0, 0};
    colonies[0].id      = 0;

    //skip over colony 0
    for (unsigned i = 1; i < NUM_COLONIES; i++)
    {
        auto& col    = colonies[i];
        col.colour   = m_colours[i];
        col.id       = i;
    }

    return colonies;
}


/*
    //Set up the colony data and choose locations for the colonies
    std::array<sf::Vector2i, NUM_COLONIES> colonyLocations;
    for (unsigned i = 1; i < NUM_COLONIES; i++)
    {
        auto& colony    = m_colonies[i];
        colony.id       = id++;
        colony.colour   = getColour(id);
        //colony.startStrLow  = 500;
        //colony.startStrHigh = Random::get().intInRange(900, 2000);

        //Find a on-land location for the colony to originate from
        int x, y;
        bool locationFound = false;
        while (!locationFound)
        {
            x = Random::get().intInRange(0, m_pConfig->width);
            y = Random::get().intInRange(0, m_pConfig->height);

            auto pixel = m_pConfig->image.getPixel(x, y);
            if (pixel.g >= 250)
            {
                locationFound = true;
                colonyLocations[i] = {x, y};
            }
        }
    }
*/
