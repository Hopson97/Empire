#ifndef COLONY_H_INCLUDED
#define COLONY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <array>

struct Config;
class Map;

struct Colony {
    unsigned id;
    unsigned startPeople = 50;

    sf::Color colour;

    unsigned strLow;
    unsigned strHigh;
};

#endif // COLONY_H_INCLUDED
