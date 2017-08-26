#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Config.h"


const sf::Color& getColour(int i);

unsigned getIndex(unsigned width, unsigned x, unsigned y);

template<typename F>
void cellForEach(const Config& config, F f)
{
    for (unsigned y = 0; y < config.height; y++)
    {
        for (unsigned x = 0; x < config.width; x++)
        {
            f(x, y);
        }
    }
}



#endif // COMMON_H_INCLUDED
