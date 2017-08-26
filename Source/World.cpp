#include "World.h"

#include <iostream>
#include <iomanip>

#include "Random.h"
#include "Common.h"
#include "Config.h"



World::World(const Config& config)
:   m_people    (config.width * config.height)
,   m_pConfig   (&config)
{
    m_worldTexture.loadFromImage(config.image);
    m_world.setTexture  (&m_worldTexture);
    m_world.setSize     ({config.width, config.height});


    createColonies();
    initText();
}

void World::update()
{
    for (auto& c : m_colonyCount)
    {
        c.members = 0;
        c.strength = 0;
    }

    std::vector<Person> newPeople(m_pConfig->width * m_pConfig->height);

    for (unsigned y = 0; y < m_pConfig->height; y++)
    for (unsigned x = 0; x < m_pConfig->width; x++)
    {
        auto& person = m_people[getIndex(m_pConfig->width, x, y)];
        auto& counter = m_colonyCount[person.getData().colony];


        if (!person.getData().isAlive)
            continue;
        person.update();
        if (!person.getData().isAlive)
            continue;


        //Get new location to move to
        int xMoveTo = x + Random::get().intInRange(-1, 1);
        int yMoveTo = y + Random::get().intInRange(-1, 1);
        if (xMoveTo < 0 || xMoveTo >= (int)m_pConfig->width) continue;
        if (yMoveTo < 0 || yMoveTo >= (int)m_pConfig->height) continue;

        //Store this for the counter to use at the end of the loop
        auto  strength      = person.getData().strength;
        auto& counterMems   = counter.members;
        auto& counterStr    = counter.strength;
        auto& movePerson    = m_people[getIndex(m_pConfig->width, xMoveTo, yMoveTo)];

        //If trying to move onto water, stay put
        if (m_pConfig->image.getPixel(xMoveTo, yMoveTo).b > 0)
        {
            newPeople[getIndex(m_pConfig->width, x, y)] = person;
            continue;
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
                    continue;
                }
            }
        }
        //if the fight is survived, then good news!
        newPeople[getIndex(m_pConfig->width, xMoveTo, yMoveTo)] = person;

        //try give birth
        if (person.getData().productionCount >= REPRODUCE_THRESHOLD)
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
        newPeople[getIndex(m_pConfig->width, x, y)] = person;


        //Finally, do stuff for the counter
        counterMems ++;
        counterStr  += strength;

    }
    m_people = std::move(newPeople);
}

const sf::Color& World::getColorAt(unsigned x, unsigned y)
{
    return m_colonies[m_people[getIndex(m_pConfig->width, x, y)].getData().colony].colour;
}


void World::draw(sf::RenderWindow& window)
{
    window.draw(m_world);
}

void World::drawText(sf::RenderWindow& window)
{
    for (auto& counter : m_colonyCount)
    {
        std::ostringstream stream;

        int averageStr = (counter.members > 0) ?
            counter.strength / counter.members :
            0;


        stream  << std::left
                << std::setw(10)    << counter.name
                << std::setw(7)     << counter.members
                << std::setw(10)    << " Avg Str: " << averageStr << '\n';

        counter.text.setString(stream.str());
        window.draw(counter.text);
    }
}

void World::createColonies()
{
    //First colony type is just nothingness
    int id = 0;
    m_colonies[0].colour = {0, 0, 0, 0};
    m_colonies[0].id = id++;

    //Set up the colony data and choose locations for the colonies
    std::array<sf::Vector2i, NUM_COLONIES> colonyLocations;
    for (unsigned i = 1; i < m_colonies.size(); i++)
    {
        auto& colony    = m_colonies[i];
        colony.id       = id++;
        colony.colour   = getColour(id);

        //Find a on-land location for the colony to originate from
        int x, y;
        bool locationFound = false;
        while (!locationFound)
        {
            x = Random::get().intInRange(0, m_pConfig->width);
            y = Random::get().intInRange(0, m_pConfig->height);

            auto pixel = m_pConfig->image.getPixel(x, y);
            if (pixel.g >= 250)
            {
                locationFound = true;
                colonyLocations[i] = {x, y};
            }
        }
    }

    //Place colonies at the locations
    for (unsigned i = 1; i < NUM_COLONIES; i++)
    {
        auto& location = colonyLocations[i];
        //place up to 50 people at the location
        for (int j = 0; j < 50; j++)
        {
            int xOffset = Random::get().intInRange(-4, 4);
            int yOffset = Random::get().intInRange(-4, 4);

            int newLocationX = xOffset + location.x;
            int newLocationY = yOffset + location.y;

            if (newLocationX < 0 || newLocationX >= (int)m_pConfig->width) continue;
            if (newLocationY < 0 || newLocationY >= (int)m_pConfig->height) continue;
            if (m_pConfig->image.getPixel(newLocationX, newLocationY).g < 250) continue;

            PersonData data;
            data.age        = 0;
            data.strength   = Random::get().intInRange(500, 600);
            data.isAlive    = true;
            data.colony     = i;

            m_people[getIndex(m_pConfig->width, newLocationX, newLocationY)].init(data);

        }
    }
}

void World::initText()
{
    int charSize = 18;
    m_counterFont.loadFromFile("res/arial.ttf");

    for (int i = 0; i < NUM_COLONIES; i++)
    {
        ColonyCount& counter = m_colonyCount[i];
        counter.name = "Colony " + std::to_string(i) + ": ";
        counter.text.setCharacterSize(charSize);
        counter.text.move(10, m_pConfig->height - i * charSize - 30);
        counter.text.setOutlineColor(sf::Color::Black);
        counter.text.setFillColor(m_colonies[i].colour);
        counter.text.setOutlineThickness(1);
        counter.text.setFont(m_counterFont);
    }
}























