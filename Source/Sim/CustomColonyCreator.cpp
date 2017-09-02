#include "CustomColonyCreator.h"

#include <fstream>
#include <iostream>

#include "../Native/Native.h"
#include "../Util/Random.h"
#include "../Util/Config.h"

#include "Map.h"
#include "../Native/Native.h"

CustomColonyCreator::CustomColonyCreator(int numColonies, const std::string& fileName)
:   ColonyCreator   (numColonies)
{
    std::ifstream inFile("Res/Starts/" + fileName + ".txt");

    if (!inFile.is_open())
    {
        std::cout << "Unable to open" << fileName << '\n';
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        if (line == "COLONY")
        {
            bool    startFound      = false,
                    strengthFound   = false,
                    peopleFound     = false,
                    colourFound     = false;
            ColonyInfo info;

            while (line != "END")
            {
                std::getline(inFile, line);
                if (line == "START")
                {
                    loadStartPoint(info, inFile);
                    startFound = true;
                }
                else if (line == "STRENGTH")
                {
                    loadStrength(info, inFile);
                    strengthFound = true;
                }
                else if (line == "PEOPLE")
                {
                    peopleFound = true;
                    inFile >> info.people;
                    if (info.people < 0)
                    {
                        printError("PEOPLE");
                        info.people = 100;
                    }
                }
                else if (line == "COLOUR")
                {
                    colourFound = true;
                    inFile >> info.colour.r >> info.colour.g >> info.colour.b;
                }
            }

            std::cout   << std::boolalpha
                        << startFound << " "
                        << strengthFound << " "
                        << peopleFound << " "
                        << colourFound << "\n";

            if (startFound && strengthFound && peopleFound && colourFound)
            {
                m_colonyInfo.push_back(info);
            }
            else
            {
                std::cout   << TextColour::Red
                            << "Failed to load colony, section missing\n"
                            << TextColour::Default;
            }
        }
    }
}


std::vector<sf::Vector2i> CustomColonyCreator::createColonyLocations(const Config& config, const Map& map) const
{
    std::vector<sf::Vector2i> locations(m_colonyInfo.size());

    //skip over colony 0
    for (unsigned i = 1; i < m_colonyInfo.size(); i++)
    {
        int x, y;
        //Loops until land is found

        x = m_colonyInfo[i].startPoint.x;
        y = m_colonyInfo[i].startPoint.y;
        if (!map.isLandAt(x, y))
        {
            std::cout << "WARNING: COLONY OVER WATER.\n";
        }

        locations[i] = {x, y};
    }

    return locations;
}

std::vector<Colony> CustomColonyCreator::createColonyStats() const
{
    std::vector<Colony> colonies(m_colonyInfo.size() + 1);

    //Colony 0 is reserved for the dead
    colonies[0].colour  = {0, 0, 0, 0};
    colonies[0].id      = 0;

    //skip over colony 0
    for (unsigned i = 1; i < m_colonyInfo.size() + 1; i++)
    {
        auto& col   = colonies[i];
        auto& info  = m_colonyInfo[i];

        col.strLow  = info.strLow;
        col.strHigh = info.strHigh;
        col.colour  = info.colour;
        col.startPeople = info.people;
        col.id = i;
    }

    return colonies;
}

void CustomColonyCreator::loadStartPoint(ColonyInfo& info, std::ifstream& inFile)
{
    inFile >> info.startPoint.x >> info.startPoint.y;

    if (info.strLow < 0)
    {
        printError("START POINT");
        info.startPoint.x = 100;
    }
    if (info.strHigh < 0)
    {
        printError("START POINT");
        info.startPoint.y = 100;
    }
}

void CustomColonyCreator::loadStrength(ColonyInfo& info, std::ifstream& inFile)
{
    inFile >> info.strLow >> info.strHigh;
    if (info.startPoint.x < 0)
    {
        printError("STRENGTH");
        info.strLow = 100;
    }
    if (info.startPoint.y < 0)
    {
        printError("STRENGTH");
        info.strHigh = 100;
    }
}

void CustomColonyCreator::printError (const std::string& name)
{
    std::cout   << TextColour::Red
                << name << "COORDS> MUST BE GREATER THAN 0, setting to 100.\n\n"
                << TextColour::Default;
}


