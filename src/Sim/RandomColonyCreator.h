#ifndef RANDOMCOLONYCREATOR_H_INCLUDED
#define RANDOMCOLONYCREATOR_H_INCLUDED

#include "ColonyCreator.h"

class RandomColonyCreator : public ColonyCreator {
  public:
    RandomColonyCreator(int numColonies);

    std::vector<sf::Vector2i> createColonyLocations(const Config& config,
                                                    const Map& map) const override;
    std::vector<Colony> createColonyStats() const override;

  private:
    int m_numColonies;

    std::vector<sf::Color> m_colours;
};

#endif // RANDOMCOLONYCREATOR_H_INCLUDED
