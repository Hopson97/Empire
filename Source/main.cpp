#include "Application.h"

#include <iostream>

int main(int argc, char** argv)
{
    Config config;
    if (argc == 1)
    {
        std::cout << "No arguments, using default (World Map)\n";
        config.image.loadFromFile("res/world_map.png");
        config.width    = config.image.getSize().x;
        config.height   = config.image.getSize().y;
    }
    else
    {
        std::string file = argv[1];
        std::cout << "Using " << file << "\n";
        config.image.loadFromFile(file);
        config.width    = config.image.getSize().x;
        config.height   = config.image.getSize().y;
    }


    Application app(config);
    app.run();
}
