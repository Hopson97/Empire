#include "ColonyCreator.h"

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


