#include <iostream>
#include <fstream>

#include "Util/Config.h"
#include "Application.h"

void parseConfig    (std::ifstream& inFile, Config& configFile);
void printConfigTips();
void printControls  ();

int main()
{
    Config configFile;

    std::cout << "Trying to load image...\n";

    std::ifstream inFile("config.txt");
    if (!inFile.is_open())
    {
        std::cerr << "Unable to open config, using default.\n";
        configFile.image.loadFromFile("Res/Maps/world_map_large.png");
    }
    else
    {
        parseConfig(inFile, configFile);
    }

    printConfigTips ();
    printControls   ();

    configFile.width    = configFile.image.getSize().x;
    configFile.height   = configFile.image.getSize().y;

    Application app(configFile);
    app.run();
}

void parseConfig(std::ifstream& inFile, Config& configFile)
{

    std::string str;
    while (std::getline(inFile, str))
    {
        if (str == "IMAGE")
        {
            inFile >> str;
            if (!configFile.image.loadFromFile("Res/" + str))
            {
                std::cerr << "Unable to open \"" << str << "\", using default.\n\n";
                configFile.image.loadFromFile("Res/Maps/world_map_large.png");
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
                        << configFile.colonies++ << ".\n\n";
            if (configFile.colonies <= 2)
            {
                std::cout << "Colony count too low! Setting to MIN [3]\n";
                configFile.colonies = 3;
            }
            else if (configFile.colonies > 400)
            {
                std::cout << "Colony count too high! Setting to MAX [400]\n";
                configFile.colonies = 400;
            }
        }
    }
}

void printConfigTips()
{
    std::cout   << "\nIf you want to customise your experience, then simply edit the values in config.txt. \nRecommended:\n"
                << "Image:          world_map_full.png [Put a pic in the Res/Maps/ folder, must be green and blue]\n"
                << "Reproduction:   8  [This is the threshold of reproduction, lower = higher birthrate]\n"
                << "Colonies:       10 [This is the number of colonies the simulation begins with]\n"
                << "Bare in mind, setting the colony count too high can cause CRASHES, hence it will check your number, and change it if you set it too high\n"
                << "Enjoy!\n\n";
}

void printControls  ()
{
    std::cout << "Controls: "
                << "P -> Prints a screenshot of the people (without the background).\n"
                << "See console window for the location and image name\n"
                << "\n\n";
}
