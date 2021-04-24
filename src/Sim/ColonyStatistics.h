#ifndef COLONYSTATISTICS_H_INCLUDED
#define COLONYSTATISTICS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

#include "Colony.h"

struct ColonyStatistics {
    unsigned highestStrength = 0;
    unsigned strength = 0;
    unsigned members = 0;
    sf::Text text;
    std::string name;
};

// Manages the updating and rendering of colony statistics
class ColonyStatsManager {
  public:
    ColonyStatsManager(unsigned colonyCount);

    void initText(const std::vector<Colony>& colonies);

    void reset();
    void update(unsigned colonyID, unsigned strength);

    void drawStats(sf::RenderWindow& window);

  private:
    std::vector<ColonyStatistics> m_colonyStats;
    sf::RectangleShape m_colonyStatsBg;
    sf::Text m_totalPopText;
};

#endif // COLONYSTATISTICS_H_INCLUDED
