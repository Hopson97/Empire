#include "Application.h"

#include <iostream>
#include <fstream>

void parseConfig(std::ifstream& inFile, Config& configFile)
{

    std::string str;
    while (std::getline(inFile, str))
    {
        if (str == "IMAGE")
        {
            inFile >> str;
            if (!configFile.image.loadFromFile("res/" + str))
            {
                std::cerr << "Unable to open \"" << str << "\", using default.\n\n";
                configFile.image.loadFromFile("res/world_map_large.png");
            }
            else
            {
                std::cout << "Success! Using " << str << ".\n\n";
            }
        }
        else if (str == "REPRODUCTION")
        {
            inFile >> configFile.reproductionThreshold;
            std::cout   << "Reproduction Threshold loaded, set to: "
                        << configFile.reproductionThreshold << ".\n\n";
        }
        else if (str == "COLONIES")
        {
            inFile >> configFile.colonies;
            std::cout   << "Colony Count loaded, set to: "
                        << configFile.colonies << ".\n\n";

            if (configFile.colonies < 0)
            {
                std::cout << "Colony count too low! Set to 10\n\n";
                configFile.colonies = 10;
            }
            else if (configFile.colonies > 12)
            {
                std::cout << "Colony count too high! Set to 10\n\n";
                configFile.colonies = 10;
            }
        }
    }
}

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
        parseConfig(inFile, configFile);
    }

    std::cout   << "\nIf you want to customise your experience, then simply edit the values in config.txt. \nRecommended:\n"
                << "Image:          world_map_full.png\n"
                << "Reproduction:   8  [This is the threshold of reproduction, lower = higher birthrate]\n"
                << "Colonies:       10 [This is the number of colonies the simulation begins with]\n"
                << "Enjoy!\n";

    configFile.width    = configFile.image.getSize().x;
    configFile.height   = configFile.image.getSize().y;

    Application app(configFile);
    app.run();
}
