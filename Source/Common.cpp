#include "Common.h"

#include <vector>

#include "Random.h"

unsigned getIndex(unsigned x, unsigned y)
{
    return y * WIDTH + x;
}

const sf::Color& getColour(int i)
{
    static std::vector<sf::Color> colours
    {
        {255,   0,      0},
        {235,   0,      171},
        {235,   0,      255},
        {110,   0,      255},
        {20,    63,     127},
        {0,     100,    255},
        {255,   255,    0},
        {255,   255,    255},
        {0,     0,      0},
        {255,   150,    0},
        {145,   85,     26},
    };

    return colours[i];
}
