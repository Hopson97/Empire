#include "Application.h"

#include <iostream>
#include <fstream>

int main()
{
    Config configFile;

    std::cout << "Trying to load image...\n";

    std::ifstream inFile("config.txt");
    if (!inFile.is_open())
    {
        std::cerr << "Unable to open config, using default.\n";
        configFile.image.loadFromFile("res/world_map_large.png");
    }
    else
    {
        std::string file;
        inFile >> file;
        if (!configFile.image.loadFromFile("res/" + file))
        {
            std::cerr << "Unable to open \"" << file << "\", using default.\n";
            configFile.image.loadFromFile("res/world_map_large.png");
        }
        else
        {
            std::cout << "Success! Using " << file << "!\n";
        }
    }

    std::cout   << "\n If you want change the map, add an image to the res folder and\n"
                << "change the image name in \"config.txt\". Enjoy!\n"
                << "Note: Your map must be green and blue!\n";

    configFile.width    = configFile.image.getSize().x;
    configFile.height   = configFile.image.getSize().y;

    Application app(configFile);
    app.run();
}
