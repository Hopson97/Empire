#include "World.h"

#include <iostream>

#include "Random.h"
#include "Common.h"

World::World()
:   m_people(WIDTH * HEIGHT)
{
    m_worldTexture.loadFromFile("res/world_map.png");
    m_world.setTexture  (&m_worldTexture);
    m_world.setSize     ({1280, 720});

    m_worldImage.loadFromFile("res/world_map.png");
    m_worldTexture.loadFromImage(m_worldImage);


    createColonies();
    initText();
}

void World::update()
{
    for (auto& c : m_colonyCount) c.members = 0;

    std::vector<Person> newPeople(WIDTH * HEIGHT);

    for (unsigned y = 0; y < HEIGHT; y++)
    for (unsigned x = 0; x < WIDTH; x++)
    {
        auto& person = m_people[getIndex(x, y)];
        auto& counter = m_colonyCount[person.getData().colony];

        if (!person.getData().isAlive) continue;

        person.update();

        int xMoveTo = x + Random::get().intInRange(-1, 1);
        int yMoveTo = y + Random::get().intInRange(-1, 1);

        if (xMoveTo < 0 || xMoveTo >= (int)WIDTH) continue;
        if (yMoveTo < 0 || yMoveTo >= (int)HEIGHT) continue;
        if (m_worldImage.getPixel(xMoveTo, yMoveTo).b > 0)
        {
            //if it is going to be water (blue > 0) then the person stays put
            //But, the person still needs to be copied into the new array
            counter.members++;
            newPeople[getIndex(x, y)] = person;
            continue;
        }
        else
        {
            //Try move to new location
            auto& other = m_people[getIndex(xMoveTo, yMoveTo)];
            if (other.getData().colony != person.getData().colony)
            {
                person.fight(other);
                if (!person.getData().isAlive)
                    continue;
                else
                    counter.members++;
            }
        }

        //if it is not water, then the person moves there
        counter.members++;
        newPeople[getIndex(xMoveTo, yMoveTo)] = person;

        //Try give birth
        if (person.getData().productionCount >= REPRODUCE_THRESHOLD)
        {
            counter.members++;
            person.init(person.getChild());
        }
        else
        {
            counter.members--;
            //Because they move somewhere else, the person who was there is "dead" #solution
            person.kill();
        }

        //This will either be a dead person, or a newborn
        newPeople[getIndex(x, y)] = person;

    }
    m_people = std::move(newPeople);
}

const sf::Color& World::getColorAt(unsigned x, unsigned y)
{
    return m_colonies[m_people[getIndex(x, y)].getData().colony].colour;
}


void World::draw(sf::RenderWindow& window)
{
    window.draw(m_world);

    for (auto& counter : m_colonyCount)
    {
        counter.text.setString(counter.name + std::to_string(counter.members));
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
        auto& colony = m_colonies[i];
        colony.id = id++;
        colony.colour = getRandomColour();

        //Find a on-land location for the colony to originate from
        int x, y;
        bool locationFound = false;
        while (!locationFound)
        {
            x = Random::get().intInRange(0, WIDTH);
            y = Random::get().intInRange(0, HEIGHT);

            auto pixel = m_worldImage.getPixel(x, y);
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

            if (newLocationX < 0 || newLocationX >= (int)WIDTH) continue;
            if (newLocationY < 0 || newLocationY >= (int)HEIGHT) continue;
            if (m_worldImage.getPixel(newLocationX, newLocationY).g < 250) continue;

            PersonData data;
            data.age        = 0;
            data.strength   = Random::get().intInRange(500, 600);
            data.isAlive    = true;
            data.colony     = i;

            m_people[getIndex(newLocationX, newLocationY)].init(data);

        }
    }
}

void World::initText()
{
    int charSize = 15;
    m_counterFont.loadFromFile("res/arial.ttf");

    for (int i = 0; i < NUM_COLONIES; i++)
    {
        ColonyCount& counter = m_colonyCount[i];
        counter.name = "Colony " + std::to_string(i) + ": ";
        counter.text.setCharacterSize(charSize);
        counter.text.move(0, i * charSize + 5);
        counter.text.setOutlineColor(sf::Color::Black);
        counter.text.setFillColor(m_colonies[i].colour);
        counter.text.setOutlineThickness(1);
        counter.text.setFont(m_counterFont);
    }
}























