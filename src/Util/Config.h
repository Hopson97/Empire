#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <SFML/Graphics.hpp>

struct Config {
    std::string imageName;
    sf::Image image;
    unsigned width;
    unsigned height;

    int reproductionThreshold = 8;
    int colonies = 10;

    bool customStart = false;
};

#endif // CONFIG_H_INCLUDED
