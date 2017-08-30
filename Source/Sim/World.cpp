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
:   m_people        (config.width, config.height)
,   m_colonies      (config.colonies)
,   m_colonyStats   (config.colonies)
,   m_pConfig       (&config)
{
    m_worldTexture.loadFromImage(config.image);
    m_world.setTexture  (&m_worldTexture);
    m_world.setSize     ({(float)config.width,
                          (float)config.height});
    createColonies();
    initText();
}

void World::update(sf::Image& image)
{
    Grid<Person> newPeople(m_pConfig->width, m_pConfig->height);

    for (auto& c : m_colonyStats)
    {
        c.highestStrength = 0;
        c.members = 0;
        c.strength = 0;
    }

    randomCellForEach(*m_pConfig, [&](unsigned x, unsigned y)
    {

        auto& person    = m_people(x, y);
        auto& stats     = m_colonyStats[person.getData().colony];
        auto  strength  = person.getData().strength;

        //Sometimes the loop will return early.
        //If it does, then it can call these functions
        auto endAlive = [&]()
        {
            stats.highestStrength = std::max(stats.highestStrength, strength);
            stats.strength  += strength;
            stats.members ++;
            image.setPixel(x, y, getColorAt(x, y));
        };

        auto endDead = [&]()
        {
            image.setPixel(x, y, getColorAt(x, y));
        };

        if (!person.getData().isAlive)
            return;
        person.update();
        if (!person.getData().isAlive)
            return;


        //Get new location to move to
        int xMoveTo = x + Random::get().intInRange(-1, 1);
        int yMoveTo = y + Random::get().intInRange(-1, 1);

        tryWrap(xMoveTo, yMoveTo);

        //Grid square to move to
        auto& movePerson    = m_people(xMoveTo, yMoveTo);

        //If trying to move onto water or onto square where person of same colony is
        //, stay put
        if (isWater(xMoveTo, yMoveTo))
        {
            endAlive();
            newPeople(x, y) = person;
            return;
        }
        else if (movePerson.getData().colony == person.getData().colony)
        {
            if (movePerson.getData().isDiseased)
            {
                person.giveDisease();
            }

            endAlive();
            newPeople(x, y) = person;
            return;
        }


        //Try move to new spot
        //Fight other person if need be
        if (movePerson.getData().colony != person.getData().colony)
        {
            if (movePerson.getData().isAlive)
            {
                person.fight(movePerson);
                if (!person.getData().isAlive)
                {
                    endDead();
                    return;
                }
            }
        }
        //if the fight is survived, then good news!
        newPeople(xMoveTo, yMoveTo) = person;

        //try give birth
        if (person.getData().productionCount >= m_pConfig->reproductionThreshold)
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
    return m_colonies[m_people(x, y).getData().colony].colour;
}

void World::tryWrap(int& x, int& y) const
{
    if (x < 0)                              x = (m_pConfig->width - 1) + x;
    else if (x >= (int)m_pConfig->width)    x = x - m_pConfig->width;


    if (y < 0)                              y = (m_pConfig->height - 1) + y;
    else if (y >= (int)m_pConfig->height)   y = y - m_pConfig->height;
}

bool World::isGrass(unsigned x, unsigned y) const
{
    return m_pConfig->image.getPixel(x, y).g > 235;
}

bool World::isWater(unsigned x, unsigned y) const
{
    return m_pConfig->image.getPixel(x, y).b > 235;
}

void World::draw(sf::RenderWindow& window) const
{
    window.draw(m_world);
}

void World::drawText(sf::RenderWindow& window)
{
    window.draw(m_colonyStatsBg);
    int i = 1;
    for (auto& stats : m_colonyStats)
    {
        if (stats.members == 0)
            continue;

        stats.text.setPosition(10, i++ * CHAR_SIZE + 30);

        std::ostringstream stream;

        int averageStr = abs((stats.members > 0) ?
            stats.strength / stats.members :
            0);


        stream  << std::left
                << std::setw(10) << std::left  <<  stats.name   << std::right   << '\t'
                << std::setw(7)  << std::right << stats.members << std::right   << '\t'
                << std::setw(10) << std::right << " Avg Str: "  << std::right   << averageStr << '\t'
                << std::setw(10) << std::right << " Max Str  "  << std::right   << stats.highestStrength << '\n';

        stats.text.setString(stream.str());
        window.draw(stats.text);
    }
    m_colonyStatsBg.setSize({420, i * CHAR_SIZE + 30});
}

void World::createColonies()
{
    ColonyCreator creator(m_pConfig->image, m_pConfig->colonies);

    auto locations  = creator.createColonyLocations(m_pConfig->width, m_pConfig->height);
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

            if (newLocationX < 0 || newLocationX >= (int)m_pConfig->width) continue;
            if (newLocationY < 0 || newLocationY >= (int)m_pConfig->height) continue;
            if (isWater(newLocationX, newLocationY)) continue;

            PersonData data;
            data.age        = 0;
            data.strength   = Random::get().intInRange(400, 650);
            data.isAlive    = true;
            data.colony     = i;

            m_people(newLocationX, newLocationY).init(data);

        }
    }
}

void World::initText()
{
    m_colonyStatsBg.move(4, 4);
    m_colonyStatsBg.setFillColor({128, 128, 128, 128});
    m_colonyStatsBg.setOutlineColor(sf::Color::Black);
    m_colonyStatsBg.setOutlineThickness(3);

    for (int i = 0; i < m_pConfig->colonies; i++)
    {
        auto& stats = m_colonyStats[i];
        stats.name  = "Colony " + std::to_string(i) + ": ";

        stats.text.setCharacterSize     (CHAR_SIZE);
        stats.text.setOutlineColor      (sf::Color::Black);
        stats.text.setFillColor         (m_colonies[i].colour);
        stats.text.setOutlineThickness  (1);
        stats.text.setFont              (ResourceHolder::get().fonts.get("arial"));
    }
}



