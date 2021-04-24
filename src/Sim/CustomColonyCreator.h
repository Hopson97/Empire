#ifndef CUSTOMCOLONYCREATOR_H_INCLUDED
#define CUSTOMCOLONYCREATOR_H_INCLUDED

#include "ColonyCreator.h"

class CustomColonyCreator : public ColonyCreator {
    struct ColonyInfo {
        sf::Vector2i startPoint;
        int strLow, strHigh, people;

        sf::Color colour;
    };

  public:
    CustomColonyCreator(const std::string& fileName);

    std::vector<sf::Vector2i> createColonyLocations(const Config& config,
                                                    const Map& map) const override;
    std::vector<Colony> createColonyStats() const override;

  private:
    void loadStartPoint(ColonyInfo& info, std::ifstream& inFile);
    void loadStrength(ColonyInfo& info, std::ifstream& inFile);
    void printError(const std::string& name);

    std::vector<ColonyInfo> m_colonyInfo;
};

#endif // CUSTOMCOLONYCREATOR_H_INCLUDED
