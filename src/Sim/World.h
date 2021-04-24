#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "../Util/Grid.h"
#include "Colony.h"
#include "ColonyStatistics.h"
#include "Person.h"

#include "Map.h"

struct Config;

class World {
  public:
    World(const Config& config);

    void update(sf::Image& image);
    void drawText(sf::RenderWindow& window);

    const sf::Color& getColorAt(unsigned x, unsigned y) const;

    void draw(sf::RenderWindow& window);

  private:
    void tryWrap(int& x, int& y) const;

    void createColonies();

    Map m_map;
    Grid<Person> m_people;
    std::vector<Colony> m_colonies;
    ColonyStatsManager m_colonyStatsManager;

    const Config* m_pConfig;
};

#endif // WORLD_H_INCLUDED
