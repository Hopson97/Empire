#include <fstream>
#include <iostream>
#include <thread>

#include "Application.h"
#include "Util/Config.h"
#include "Util/Random.h"

void parseConfig(std::ifstream& inFile, Config& configFile);

int main()
{
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~ PLEASE READ THIS ~~~~~~~~~~~~~~~~~~~~\n"
              << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    Config configFile;

    std::cout << "Trying to load image...\n";

    std::ifstream inFile("config.txt");
    if (!inFile.is_open()) {
        std::cerr << "Unable to open config, using default.\n";
        configFile.image.loadFromFile("res/Maps/world_map_large.png");
    }
    else {
        parseConfig(inFile, configFile);
    }

    std::cout << "Please view the Instructions file for controls and how to\ncustomise "
                 "your experience.\n\n";

    configFile.width = configFile.image.getSize().x;
    configFile.height = configFile.image.getSize().y;

    Application app(configFile);
    app.run();
}

void parseConfig(std::ifstream& inFile, Config& configFile)
{

    std::string str;
    while (std::getline(inFile, str)) {
        if (str == "IMAGE") {
            inFile >> str;
            if (!configFile.image.loadFromFile("res/Maps/" + str)) {
                std::cerr << "Unable to open \"" << str << "\", using default.\n\n";
                configFile.image.loadFromFile("res/Maps/world_map_large.png");
            }
            else {
                configFile.imageName = str.substr(0, str.length() - 4);
                std::cout << configFile.imageName << "\n";
                std::cout << "Success! Using " << str << ".\n\n";
            }
        }
        else if (str == "CUSTOM_START") {
            inFile >> configFile.customStart;
            std::cout << "Custom Start Loaded, set to " << std::boolalpha
                      << configFile.customStart << ".\n\n";
        }
        else if (str == "REPRODUCTION") {
            inFile >> configFile.reproductionThreshold;
            std::cout << "Reproduction Threshold loaded, set to: "
                      << configFile.reproductionThreshold << ".\n\n";
        }
        else if (str == "COLONIES") {
            inFile >> configFile.colonies;
            std::cout << "Colony Count loaded, set to: " << configFile.colonies++
                      << ".\n\n";

            if (configFile.colonies <= 2) {
                std::cout << "Colony count too low! Setting to MIN [3]\n";
                configFile.colonies = 3;
            }
            else if (configFile.colonies > 400) {
                std::cout << "Colony count too high! Setting to MAX [400]\n";
                configFile.colonies = 400;
            }
        }
    }
}
