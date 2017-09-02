#ifndef COLONYCREATOR_H_INCLUDED
#define COLONYCREATOR_H_INCLUDED

#include <vector>

#include "Colony.h"

class ColonyCreator
{
    public:
        ColonyCreator(int numColonies);

        virtual std::vector<sf::Vector2i>  createColonyLocations(const Config& config, const Map& map) const = 0;
        virtual std::vector<Colony>        createColonyStats() const = 0;

    protected:
        int m_numColonies;

        std::vector<sf::Color> m_colours;
};

#endif // COLONYCREATOR_H_INCLUDED
