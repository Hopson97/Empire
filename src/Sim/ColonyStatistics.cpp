#include "ColonyStatistics.h"

#include <functional>
#include <iomanip>
#include <iostream>

#include <sstream>

#include "../ResourceManager/ResourceHolder.h"

constexpr int CHAR_SIZE = 14;

ColonyStatsManager::ColonyStatsManager(unsigned colonyCount)
    : m_colonyStats(colonyCount)
{
}

void ColonyStatsManager::reset()
{
    for (auto& colonyStat : m_colonyStats) {
        colonyStat.highestStrength = 0;
        colonyStat.members = 0;
        colonyStat.strength = 0;
    }
}

void ColonyStatsManager::update(unsigned colonyID, unsigned strength)
{
    ColonyStatistics& s = m_colonyStats[colonyID];

    s.highestStrength = std::max(s.highestStrength, strength);
    s.strength += strength;
    s.members++;
}

void ColonyStatsManager::drawStats(sf::RenderWindow& window)
{
    window.draw(m_colonyStatsBg);

    int i = 2;
    int totalMembers = 0;
    for (auto& stats : m_colonyStats) {
        totalMembers += stats.members;

        if (stats.members == 0)
            continue;

        stats.text.setPosition(10, i++ * CHAR_SIZE + 30);

        std::ostringstream stream;

        int averageStr = stats.members > 0 ? stats.strength / stats.members : 0;

        stream << std::left << std::setw(10) << std::left << stats.name << std::right
               << '\t' << std::setw(7) << std::right << stats.members << std::right
               << '\t' << std::setw(10) << std::right << " Avg Str: " << std::right
               << averageStr << '\t' << std::setw(10) << std::right << " Max Str  "
               << std::right << stats.highestStrength << '\n';

        stats.text.setString(stream.str());
        window.draw(stats.text);
    }

    m_totalPopText.setString("Total Population: " + std::to_string(totalMembers));
    m_totalPopText.setPosition(10, CHAR_SIZE + 30);
    window.draw(m_totalPopText);

    m_colonyStatsBg.setSize({355, float(i * CHAR_SIZE + 30)});
}

void ColonyStatsManager::initText(const std::vector<Colony>& colonies)
{
    m_colonyStatsBg.move(4, 4);
    m_colonyStatsBg.setFillColor({128, 128, 128, 230});
    m_colonyStatsBg.setOutlineColor(sf::Color::Black);
    m_colonyStatsBg.setOutlineThickness(3);

    for (unsigned i = 0; i < colonies.size(); i++) {
        auto& stats = m_colonyStats[i];
        stats.name = "Colony " + std::to_string(i) + ": ";

        stats.text.setCharacterSize(CHAR_SIZE);
        stats.text.setOutlineColor(sf::Color::Black);
        stats.text.setFillColor(colonies[i].colour);
        stats.text.setOutlineThickness(1);
        stats.text.setFont(ResourceHolder::get().fonts.get("arial"));
    }

    m_totalPopText.setCharacterSize(CHAR_SIZE);
    m_totalPopText.setOutlineColor(sf::Color::Black);
    m_totalPopText.setFillColor(sf::Color::White);
    m_totalPopText.setOutlineThickness(1);
    m_totalPopText.setFont(ResourceHolder::get().fonts.get("arial"));
}
