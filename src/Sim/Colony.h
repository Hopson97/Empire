#ifndef COLONY_H_INCLUDED
#define COLONY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <array>

struct Config;
class Map;

struct Colony {
    unsigned id = 0;
    unsigned startPeople = 50;

    sf::Color colour;

    unsigned strLow = 0;
    unsigned strHigh = 0;
};

#endif // COLONY_H_INCLUDED
