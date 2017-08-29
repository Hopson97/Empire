#include <iostream>
#include <fstream>

#include "Util/Config.h"
#include "Application.h"
#include "Native/Native.h"

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
            if (!configFile.image.loadFromFile("Res/Maps/" + str))
            {
                std::cerr << TextColour::Red << "Unable to open \"" << str << "\", using default.\n\n" << TextColour::White;
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
            std::cout   << TextColour::Green << "Reproduction Threshold loaded, set to: "
                        << configFile.reproductionThreshold
                        << ".\n\n" << TextColour::White;
        }
        else if (str == "COLONIES")
        {
            inFile >> configFile.colonies;
            std::cout   << TextColour::Green << "Colony Count loaded, set to: "
                        << configFile.colonies++
                        << ".\n\n" << TextColour::White;

            if (configFile.colonies <= 2)
            {
                std::cout << TextColour::Red << "Colony count too low! Setting to MIN [3]\n" << TextColour::White;
                configFile.colonies = 3;
            }
            else if (configFile.colonies > 400)
            {
                std::cout << TextColour::Red << "Colony count too high! Setting to MAX [400]\n" << TextColour::White;
                configFile.colonies = 400;
            }
        }
    }
}

void printConfigTips()
{
    std::cout   << "\nIf you want to customise your experience, then simply edit the values in config.txt. \nRecommended:\n"
                << TextColour::Cyan << "Image:          world_map_full.png [Put a pic in the Res/Maps/ folder, must be green and blue]\n"
                << TextColour::Cyan << "Reproduction:   8  [This is the threshold of reproduction, lower = higher birthrate]\n"
                << TextColour::Cyan << "Colonies:       10 [This is the number of colonies the simulation begins with]\n"
                << TextColour::Red << "Bare in mind, setting the colony count too high can cause CRASHES, hence it will check your number, and change it if you set it too high\n"
                << TextColour::White << "Enjoy!\n\n";
}

void printControls  ()
{
    std::cout << TextColour::Cyan << "Controls: "
                << "P -> Prints a screenshot of the people (without the background).\n"
                << "See console window for the location and image name\n"
                << "\n\n" << TextColour::White;
}
