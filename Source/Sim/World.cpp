#include "World.h"
#include "Biome.h"

#include <iostream>
#include <iomanip>
#include <functional>

#include <type_traits>

#include "../Util/Random.h"
#include "../Util/Common.h"
#include "../Util/Config.h"
#include "../ResourceManager/ResourceHolder.h"

constexpr int CHAR_SIZE = 15;

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
        auto&  person    = m_people(x, y);
        auto&  stats     = m_colonyStats[person.getData().colony];
        auto&  biome     = Biome::getBiomeForColor(getPixelAt(x, y));

        if (!person.getData().isAlive)
            return;
        biome->onUpdate(person);
        person.update();
        if (!person.getData().isAlive)
            return;

        //Get new location to move to
        int xMoveTo = x + Random::get().intInRange(-1, 1);
        int yMoveTo = y + Random::get().intInRange(-1, 1);

        if (xMoveTo < 0 || xMoveTo >= (int)m_pConfig->width)    return;
        if (yMoveTo < 0 || yMoveTo >= (int)m_pConfig->height)   return;

        //Store this for the stats to use at the end of the loop
        auto  strength      = person.getData().strength;
        auto& movePerson    = m_people(xMoveTo, yMoveTo);
        auto& moveBiome     = Biome::getBiomeForColor(getPixelAt(xMoveTo, yMoveTo));

        //If trying to move onto water or onto square where person of same colony is
        //, stay put
        if (!moveBiome->canMove(person.getData()))
        {
            stats.highestStrength = std::max(stats.highestStrength, strength);
            stats.strength    += strength;
            stats.members     ++;
            newPeople(x, y) = person;
            image.setPixel(x, y, getColorAt(x, y));
            return;
        }
        else if (movePerson.getData().colony == person.getData().colony)
        {
            stats.highestStrength = std::max(stats.highestStrength, strength);
            stats.strength  += strength;
            stats.members ++;

            if (movePerson.getData().isDiseased)
            {
                person.giveDisease();
            }

            newPeople(x, y) = person;
            image.setPixel(x, y, getColorAt(x, y));
            return;
        }


        //Try move to new spot
        //Fight other person if need be
        if (movePerson.getData().colony != person.getData().colony)
        {
            if (movePerson.getData().isAlive)
            {
                moveBiome->onFight(movePerson, person);
                person.fight(movePerson);
                if (!person.getData().isAlive)
                {
                    image.setPixel(x, y, getColorAt(x, y));
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
            auto childData = person.getChild();
            biome->onRepopulate(childData);
            person.init(childData);
        }
        else
        {
            //Kill the old person, the current person has now moved
            person.kill();
        }

        //This will either be a dead person, or a newborn
        newPeople(x, y) = person;


        //Finally, do stuff for the stats
        stats.members ++;
        stats.strength  += strength;
        stats.highestStrength = std::max(stats.highestStrength, strength);
        image.setPixel(x, y, getColorAt(x, y));
    });
    m_people = std::move(newPeople);
}

const sf::Color& World::getColorAt(unsigned x, unsigned y) const
{
    return m_colonies[m_people(x, y).getData().colony].colour;
}

bool World::isGrass(unsigned x, unsigned y) const
{
    return m_pConfig->image.getPixel(x, y).g > 235;
}

bool World::isWater(unsigned x, unsigned y) const
{
    return m_pConfig->image.getPixel(x, y).b > 235;
}

sf::Color World::getPixelAt(unsigned x, unsigned y) const
{
    return m_pConfig->image.getPixel(x, y);
}

void World::draw(sf::RenderWindow& window) const
{
    window.draw(m_world);
}

void World::drawText(sf::RenderWindow& window)
{
    int i = 0;
    for (auto& stats : m_colonyStats)
    {
        if (stats.members == 0)
            continue;

        stats.text.setPosition(0, i++ * CHAR_SIZE + 30);

        std::ostringstream stream;

        int averageStr = abs((stats.members > 0) ?
            stats.strength / stats.members :
            0);


        stream  << std::left
                << std::setw(10)    << stats.name
                << std::setw(7)     << stats.members
                << std::setw(10)    << " Avg Str: " << averageStr
                << std::setw(10)    << " Max Str  " << stats.highestStrength << '\n';

        stats.text.setString(stream.str());
        window.draw(stats.text);
    }
}

void World::createColonies()
{
    ColonyCreator creator(m_pConfig->image, m_pConfig->colonies);

    auto locations  = creator.createColonyLocations(m_pConfig->width, m_pConfig->height);
    m_colonies      = creator.createColonyStats();

    std::cout << "limits: " << m_pConfig->width << ", " << m_pConfig->height << "\n";

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

            PersonData data;
            data.age        = 0;
            data.strength   = Random::get().intInRange(400, 650);
            data.isAlive    = true;
            data.colony     = i;

            std::cout << "["<< i << ", " << j << "] x: " << newLocationX << ", y: " << newLocationY << "\n";
            auto& biome = Biome::getBiomeForColor(getPixelAt(newLocationX, newLocationY));
            if (!biome || !biome->canMove(data)) continue;
            std::cout << "cleared\n";

            m_people(newLocationX, newLocationY).init(data);

        }
    }
}

void World::initText()
{
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



