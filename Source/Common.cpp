#include "Common.h"

#include <vector>

#include "Random.h"

unsigned getIndex(unsigned x, unsigned y)
{
    return y * WIDTH + x;
}

const sf::Color& getRandomColour()
{
    static std::vector<sf::Color> colours
    {
        {255,   255,    0},
        {0,     255,    255},
        {255,   0,      0},
        {255,   100,    0},
        {15,    245,    153},
        {7,     94,     59},
        {59,     7,     94},
        {100,   255,     0},
        {227,   130,    250},
        {255,   255,    255},
        {0,     0,      0},
        {70,    96,     129},
        {129,   70,     129},
    };

    return colours[Random::get().intInRange(0, colours.size() - 1)];
}
