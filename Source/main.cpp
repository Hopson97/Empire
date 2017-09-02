#include <iostream>
#include <fstream>
#include <thread>

#include "Util/Random.h"
#include "Util/Config.h"
#include "Application.h"
#include "Native/Native.h"

void parseConfig    (std::ifstream& inFile, Config& configFile);
void printConfigTips();
void printControls  ();

int main()
{
    std::cout   << TextColour::Red  << "\n~~~~~~~~~~~~~~~~~~~~ PLEASE READ THIS ~~~~~~~~~~~~~~~~~~~~\n"
                << TextColour::Red  << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
                << TextColour::Default;
    Config configFile;

    std::cout << "Trying to load image...\n";

    std::ifstream inFile("config.txt");
    if (!inFile.is_open())
    {
        std::cerr << TextColour::Red << "Unable to open config, using default.\n" << TextColour::Default;
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
                std::cerr << TextColour::Red << "Unable to open \"" << str << "\", using default.\n\n" << TextColour::Default;
                configFile.image.loadFromFile("Res/Maps/world_map_large.png");
            }
            else
            {
                configFile.imageName = str.substr(0, str.length() - 4);
                std::cout << configFile.imageName << "\n";
                std::cout << TextColour::Green << "Success! Using " << str << ".\n\n";
            }
        }
        else if (str == "CUSTOM_START")
        {
            inFile >> configFile.customStart;
            std::cout   << TextColour::Default << "Custom Start Loaded, set to "
                        << std::boolalpha << configFile.customStart
                        << ".\n\n" << TextColour::Default;
        }
        else if (str == "REPRODUCTION")
        {
            inFile >> configFile.reproductionThreshold;
            std::cout   << TextColour::Default << "Reproduction Threshold loaded, set to: "
                        << configFile.reproductionThreshold
                        << ".\n\n" << TextColour::Default;
        }
        else if (str == "COLONIES")
        {
            inFile >> configFile.colonies;
            std::cout   << TextColour::Default << "Colony Count loaded, set to: "
                        << configFile.colonies++
                        << ".\n\n" << TextColour::Default;

            if (configFile.colonies <= 2)
            {
                std::cout << TextColour::Red << "Colony count too low! Setting to MIN [3]\n" << TextColour::Default;
                configFile.colonies = 3;
            }
            else if (configFile.colonies > 400)
            {
                std::cout << TextColour::Red << "Colony count too high! Setting to MAX [400]\n" << TextColour::Default;
                configFile.colonies = 400;
            }
        }
    }
}

void printConfigTips()
{
    std::cout   << TextColour::DarkCyan <<  "\nIf you want to customise your experience, then simply edit the values in config.txt. \nRecommended:\n"
                << TextColour::Cyan     <<  "Image:          world_map_full.png [Put a pic in the Res/Maps/ folder, must be green and blue]\n"
                <<                          "Reproduction:   8  [This is the threshold of reproduction, lower = higher birthrate]\n"
                <<                          "Colonies:       10 [This is the number of colonies the simulation begins with]\n"
                << TextColour::Red     <<   "PLEASE NOTE, setting the colony count too high can cause CRASHES, hence it will check your number, and change it if you set it too high\n"
                << TextColour::Default <<   "Enjoy!\n\n";
}

void printControls  ()
{
    std::cout   << TextColour::Red << "Controls:\n" << TextColour::Cyan
                << "P -> Prints a screenshot of the people (without the background).\n"
                << "See console window for the location and image name.\n"
                << TextColour::Red << "Taking screenshots in future sessions WILL OVERWRITE your screenshots from previous sessions!!\n\n" << TextColour::Cyan
                << "WASD -> Pans Camera around.\n\n"
                << "Up/ Down Arrow Keys -> Zooms camera in and out.\n\n"
                << "\n\n" << TextColour::Default;
}
