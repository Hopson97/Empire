#include <iostream>
#include <fstream>
#include <thread>

#include "Util/Random.h"
#include "Util/Config.h"
#include "Application.h"
#include "Native/Native.h"

void parseConfig    (std::ifstream& inFile, Config& configFile);

int main()
{
    #ifndef __APPLE__
        std::cout << TextColour::Red << "\n~~~~~~~~~~~~~~~~~~~~ PLEASE READ THIS ~~~~~~~~~~~~~~~~~~~~\n"
                << TextColour::Red << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
                << TextColour::Default;
    #endif // ndef __APPLE__
    Config configFile;

    std::cout << "Trying to load image...\n";

    std::ifstream inFile("config.txt");
    if (!inFile.is_open())
    {
        #ifndef __APPLE__
            std::cerr << TextColour::Red << "Unable to open config, using default.\n" << TextColour::Default;
        #endif // ndef __APPLE__
        configFile.image.loadFromFile("Res/Maps/world_map_large.png");
    }
    else
    {
        parseConfig(inFile, configFile);
    }
    #ifndef __APPLE__
        std::cout << TextColour::Cyan << "Please view the Instructions file for controls and how to\ncustomise your experience.\n\n" << TextColour::Default;
    #endif // ndef __APPLE__

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
                #ifndef __APPLE__
                    std::cerr << TextColour::Red << "Unable to open \"" << str << "\", using default.\n\n" << TextColour::Default;
                #endif // ndef __APPLE__
                configFile.image.loadFromFile("Res/Maps/world_map_large.png");
            }
            else
            {
                configFile.imageName = str.substr(0, str.length() - 4);
                std::cout << configFile.imageName << "\n";
                #ifndef __APPLE__
                    std::cout << TextColour::Green << "Success! Using " << str << ".\n\n";
                #endif // ndef __APPLE__
            }
        }
        else if (str == "CUSTOM_START")
        {
            inFile >> configFile.customStart;
            #ifndef __APPLE__
                std::cout << TextColour::Default << "Custom Start Loaded, set to "
                            << std::boolalpha << configFile.customStart
                            << ".\n\n" << TextColour::Default;
            #endif // ndef __APPLE__
        }
        else if (str == "REPRODUCTION")
        {
            inFile >> configFile.reproductionThreshold;
            #ifndef __APPLE__
                std::cout << TextColour::Default << "Reproduction Threshold loaded, set to: "
                            << configFile.reproductionThreshold
                            << ".\n\n" << TextColour::Default;
            #endif // ndef __APPLE__
        }
        else if (str == "COLONIES")
        {
            inFile >> configFile.colonies;
            #ifndef __APPLE__
                std::cout   << TextColour::Default << "Colony Count loaded, set to: "
                            << configFile.colonies++
                            << ".\n\n" << TextColour::Default;
            #endif // ndef __APPLE__

            if (configFile.colonies <= 2)
            {
                #ifndef __APPLE__
                    std::cout << TextColour::Red << "Colony count too low! Setting to MIN [3]\n" << TextColour::Default;
                #endif // ndef __APPLE__
                configFile.colonies = 3;
            }
            else if (configFile.colonies > 400)
            {
                #ifndef __APPLE__
                    std::cout << TextColour::Red << "Colony count too high! Setting to MAX [400]\n" << TextColour::Default;
                #endif // ndef __APPLE__
                configFile.colonies = 400;
            }
        }
    }
}
