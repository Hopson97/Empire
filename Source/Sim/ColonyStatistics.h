#ifndef COLONYSTATISTICS_H_INCLUDED
#define COLONYSTATISTICS_H_INCLUDED

struct ColonyStatistics
{
    int    highestStrength = 0;
    int strength    = 0;
    int members     = 0;
    sf::Text text;
    std::string name;
};

#endif // COLONYSTATISTICS_H_INCLUDED
