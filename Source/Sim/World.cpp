#include "World.h"

#include <iostream>
#include <iomanip>
#include <functional>

#include "../Util/Random.h"
#include "../Util/Common.h"
#include "../Util/Config.h"
#include "../ResourceManager/ResourceHolder.h"

constexpr int CHAR_SIZE = 14;

World::World(const Config& config)
:   m_map           (config)
,   m_people        (config.width, config.height)
,   m_colonies      (config.colonies)
,   m_colonyStatsManager    (config.colonies)
,   m_pConfig       (&config)
{
    createColonies();
    m_colonyStatsManager.initText(m_colonies);
}

void World::update(sf::Image& image)
{
    Grid<Person> newPeople(m_pConfig->width, m_pConfig->height);
    m_colonyStatsManager.reset();

    randomCellForEach(*m_pConfig, [&](unsigned x, unsigned y)
    {
        auto& person    = m_people(x, y);
        if (!person.isAlive())
            return;

        person.update();

        if (!person.isAlive()) return;


        unsigned colonyID  = person.getColony();
        unsigned strength  = person.getStrength();

        //Sometimes the loop will return early.
        //If it does, then it can call these functions
        auto endAlive = [&]()
        {
            m_colonyStatsManager.update(colonyID, strength);
            image.setPixel(x, y, getColorAt(x, y));
        };

        auto endDead = [&]()
        {
            image.setPixel(x, y, getColorAt(x, y));
        };

        //Get new location to move to
        auto moveTo = person.getNextMove();
        int xMoveTo = x + moveTo.x;
        int yMoveTo = y + moveTo.y;
        tryWrap(xMoveTo, yMoveTo);

        //Grid square to move to
        auto& movePerson = m_people(xMoveTo, yMoveTo);

        //If trying to move onto water or onto square where person of same colony is
        //, stay put
        if (m_map.isWaterAt(xMoveTo, yMoveTo))
        {
            endAlive();
            newPeople(x, y) = person;
            return;
        }
        else if (movePerson.getColony() == colonyID)
        {
            if (movePerson.isDiseased())
            {
                person.giveDisease();
            }

            endAlive();
            newPeople(x, y) = person;
            return;
        }

        //Try move to new spot
        //Fight other person if need be
        if (movePerson.getColony() != colonyID)
        {
            if (movePerson.isAlive())
            {
                person.fight(movePerson);
                if (!person.isAlive())
                {
                    endDead();
                    return;
                }
            }
        }
        //if the fight is survived, then good news!
        newPeople(xMoveTo, yMoveTo) = person;

        //try give birth
        if (person.getProduction() >= (unsigned)m_pConfig->reproductionThreshold)
        {
            //The person itself has moved to a new spot, so it is ok to mess with it's data now
            person.init(person.getChild());
        }
        else
        {
            //Kill the old person, the current person has now moved
            person.kill();
        }

        //This will either be a dead person, or a newborn
        newPeople(x, y) = person;

        endAlive();
    });
    m_people = std::move(newPeople);
}

const sf::Color& World::getColorAt(unsigned x, unsigned y) const
{
    return m_colonies[m_people(x, y).getColony()].colour;
}

void World::tryWrap(int& x, int& y) const
{
    if (x < 0)                              x = (m_pConfig->width - 1) + x;
    else if (x >= (int)m_pConfig->width)    x = x - m_pConfig->width;


    if (y < 0)                              y = (m_pConfig->height - 1) + y;
    else if (y >= (int)m_pConfig->height)   y = y - m_pConfig->height;
}

const Map& World::getMap() const
{
    return m_map;
}

void World::drawText(sf::RenderWindow& window)
{
    m_colonyStatsManager.drawStats(window);
}

void World::createColonies()
{
    ColonyCreator creator(m_pConfig->colonies);

    auto locations  = creator.createColonyLocations(*m_pConfig, m_map);
    m_colonies      = creator.createColonyStats();

    //Place colonies at the locations
    for (unsigned i = 1; i < (unsigned)m_pConfig->colonies; i++)
    {
        auto& location = locations[i];
        //place up to 50 people at the location
        for (int j = 0; j < 50; j++)
        {
            int xOffset = Random::get().intInRange(-4, 4);
            int yOffset = Random::get().intInRange(-4, 4);

            int newLocationX = xOffset + location.x;
            int newLocationY = yOffset + location.y;

            if (newLocationX < 0 || newLocationX >= (int)m_pConfig->width)  continue;
            if (newLocationY < 0 || newLocationY >= (int)m_pConfig->height) continue;
            if (m_map.isWaterAt(newLocationX, newLocationY))                continue;

            ChildData data;
            data.strength   = Random::get().intInRange(m_colonies[i].strLow,
                                                       m_colonies[i].strHigh);
            data.isDiseased = false;
            data.colony     = i;

            m_people(newLocationX, newLocationY).init(data);

        }
    }
}



