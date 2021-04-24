#include "World.h"

#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>

#include "../ResourceManager/ResourceHolder.h"
#include "../Util/Common.h"
#include "../Util/Config.h"
#include "../Util/Random.h"

#include "ColonyCreator.h"
#include "CustomColonyCreator.h"
#include "RandomColonyCreator.h"

//#define SWIMMING_ENABLED
//#define LASER_SWIMMING

constexpr int CHAR_SIZE = 14;

World::World(const Config& config)
    : m_map(config)
    , m_people(config.width, config.height)
    , m_colonyStatsManager(config.colonies)
    , m_pConfig(&config)
{
    createColonies();
    m_colonyStatsManager.initText(m_colonies);
}

const sf::Color& World::getColorAt(unsigned x, unsigned y) const
{
    return m_colonies[m_people(x, y).colony].colour;
}

void World::tryWrap(int& x, int& y) const
{
    if (x < 0)
        x = (m_pConfig->width - 1) + x;
    else if (x >= (int)m_pConfig->width)
        x = x - m_pConfig->width;

    if (y < 0)
        y = (m_pConfig->height - 1) + y;
    else if (y >= (int)m_pConfig->height)
        y = y - m_pConfig->height;
}

void World::drawText(sf::RenderWindow& window)
{
    m_colonyStatsManager.drawStats(window);
}

void World::draw(sf::RenderWindow& window)
{
    m_map.draw(window);
}

void World::createColonies()
{
    std::unique_ptr<ColonyCreator> colonyCreator;
    if (m_pConfig->customStart)
        colonyCreator = std::make_unique<CustomColonyCreator>(m_pConfig->imageName);
    else
        colonyCreator = std::make_unique<RandomColonyCreator>(m_pConfig->colonies);

    auto locations = colonyCreator->createColonyLocations(*m_pConfig, m_map);
    m_colonies = colonyCreator->createColonyStats();

    // Place colonies at the locations
    for (unsigned i = 1; i < m_colonies.size(); i++) {
        auto& location = locations[i];
        // place people at the location
        for (unsigned j = 0; j < m_colonies[i].startPeople; j++) {
            constexpr int radius = 5;
            int xOffset = Random::get().intInRange(-radius, radius);
            int yOffset = Random::get().intInRange(-radius, radius);

            int newLocationX = xOffset + location.x;
            int newLocationY = yOffset + location.y;

            if (newLocationX < 0 || newLocationX >= (int)m_pConfig->width)
                continue;
            if (newLocationY < 0 || newLocationY >= (int)m_pConfig->height)
                continue;
            if (m_map.isWaterAt(newLocationX, newLocationY))
                continue;

            ChildData data;
            data.strength =
                Random::get().intInRange(m_colonies[i].strLow, m_colonies[i].strHigh);
            data.isDiseased = false;
            data.colony = i;

            m_people(newLocationX, newLocationY).init(data);
        }
    }
}

void World::update(sf::Image& image)
{
    Grid<Person> newPeople(m_pConfig->width, m_pConfig->height);
    m_colonyStatsManager.reset();

    randomCellForEach(*m_pConfig, [&](unsigned x, unsigned y) {
        auto& person = m_people(x, y);

        if (!person.isAlive)
            return;

        person.update();

        if (!person.isAlive) {
            image.setPixel(x, y, getColorAt(x, y));
            return;
        }

        auto colonyID = person.colony;
        auto strength = person.strength;

        // Sometimes the loop will return early.
        // If it does, then it can call these functions
        auto endAlive = [&]() {
            newPeople(x, y) = person;
            m_colonyStatsManager.update(colonyID, strength);
            image.setPixel(x, y, getColorAt(x, y));
        };

        auto endDead = [&]() { image.setPixel(x, y, getColorAt(x, y)); };

        // Get new location to move to
        auto nextMove = person.getNextMove();
        int xMoveTo = x + nextMove.x;
        int yMoveTo = y + nextMove.y;
        tryWrap(xMoveTo, yMoveTo);

        // Grid square to move to
        auto& movePerson = m_people(xMoveTo, yMoveTo);

        if (m_map.isWaterAt(xMoveTo, yMoveTo)) {
#ifndef SWIMMING_ENABLED
            endAlive();
            return;
#endif      // SWIMMING_ENABLED
            ///@SWIMMING
            /*  SWIMMING enabling code. If you want to see it, then #define
               SWIMMING_ENABLED at the top of this file

                I commented this out as it didn't have results in spirit of the goals of
               this application As, with swimming, you end up with two colonies in
               equilibrium, twisted amongst each other on every island, whereas the spirit
               is huge colonies. Hence, I removed it.
            */
#ifdef SWIMMING_ENABLED
            if (!person.isSwimming) {
                if ((Random::get().intInRange(0, 10000) < 30)) {
                    person.startSwim(nextMove);
                }
                else {
                    endAlive();
                    return;
                }
            }
#endif // SWIMMING_ENABLED
        }

#ifdef SWIMMING_ENABLED
        else {
            person.endSwim();
        }
#endif // SWIMMING_ENABLED

        // For encounters with people of the same colony or others
        if (movePerson.colony == colonyID) // disease will spread
        {
            if (movePerson.isDiseased) {
                person.giveDisease();
            }

            if (person.isSwimming) {
                person.turnAround();
            }

            endAlive();
            return;
        }
        else {
            if (movePerson.isAlive) {
                person.fight(movePerson);
                if (!person.isAlive) {
                    endDead();
                    return;
                }
            }
        }

        // if the person survived, then move to the next place
        newPeople(xMoveTo, yMoveTo) = person;

        // Only reproduce over land
        if (person.isSwimming) {
// Kill the old person, the current person has now moved.
// I know this is weird, but it works :^)
#ifndef LASER_SWIMMING
            person.kill();
#endif // LASER_SWIMMING

#ifdef LASER_SWIMMING
            // Turning this on causes "laser people"(assuming swimming is enabled)
            person.init(person.getChild());
#endif // LASER_SWIMMING
        }
        else {
            if ((person.productionCount >= (unsigned)m_pConfig->reproductionThreshold)) {
                // The person itself has moved to a new spot, so it is ok to mess with
                // it's data now
                person.init(person.getChild());
            }
            else {
                // Kill the old person, the current person has now moved.
                // I know this is weird, but it works :^)
                person.kill();
            }
        }

        endAlive();
    });
    m_people = std::move(newPeople);
}
