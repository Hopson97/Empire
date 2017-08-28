#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Random.h"

unsigned getIndex(unsigned width, unsigned x, unsigned y);

//This loops the cells in a random order, eg might go from bottom left to top right,
//or top left to bottom right.
//This is there is less bias towards a certain direction
template<typename F>
void randomCellForEach(const Config& config, F f)
{
    int option = Random::get().intInRange(0, 3);
    switch (option)
    {
        case 0:
            for (unsigned y = 0; y < config.height; y++)
            {
                for (unsigned x = 0; x < config.width; x++)
                {
                    f(x, y);
                }
            }
            break;

        case 1:
            for (unsigned y = config.height - 1; y > 0; y--)
            {
                for (unsigned x = 0; x < config.width; x++)
                {
                    f(x, y);
                }
            }
            break;

        case 2:
            for (unsigned y = 0; y < config.height; y++)
            {
                for (unsigned x = config.width - 1; x > 0; x--)
                {
                    f(x, y);
                }
            }
            break;

        case 3:
            for (unsigned y = config.height - 1; y > 0; y--)
            {
                for (unsigned x = config.width - 1; x > 0; x--)
                {
                    f(x, y);
                }
            }
            break;
    }
}


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
