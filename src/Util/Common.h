#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Random.h"

unsigned getIndex(unsigned width, unsigned x, unsigned y);

enum Direction { Increase, Decrease };

template <typename F>
void iterateInDirection(Direction direction, unsigned lower_bound, unsigned upper_bound,
                        F action)
{
    switch (direction) {
        case Direction::Increase:
            for (unsigned i = lower_bound; i < upper_bound; i++) {
                action(i);
            }
            break;

        case Direction::Decrease:
            for (unsigned i = upper_bound - 1; i > lower_bound; i--) {
                action(i);
            }
            break;
    }
}

// This loops the cells in a random order, eg might go from bottom left to top right,
// or top left to bottom right.
// This is so there is less bias towards a certain direction
template <typename F>
void randomCellForEach(const Config& config, F f)
{
    auto xDir = (Direction)Random::get().intInRange(0, 1);
    auto yDir = (Direction)Random::get().intInRange(0, 1);

    iterateInDirection(yDir, 0, config.height, [&](auto y) {
        iterateInDirection(xDir, 0, config.width, [&](auto x) { f(x, y); });
    });
}

template <typename F>
void cellForEach(const Config& config, F f)
{
    iterateInDirection(Direction::Increase, 0, config.height, [&](auto y) {
        iterateInDirection(Direction::Increase, 0, config.width,
                           [&](auto x) { f(x, y); });
    });
}

#endif // COMMON_H_INCLUDED
