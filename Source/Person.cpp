#include "Person.h"

#include "Random.h"

Person::Person(const PersonData& data)
:   m_data  (data)
{
}

void Person::init(const PersonData& data)
{
    m_data = data;
}

void Person::update()
{
    m_data.age++;
    m_data.reproduceThreshold++;

    if (m_data.age >= m_data.strength)
    {
        kill();
    }
}

void Person::kill()
{
    m_data = PersonData();
}

PersonData Person::getChild()
{
    m_data.reproduceThreshold = 0;

    //14% chance of mutation, 1% chance for big mutation
    int mutation = Random::get().intInRange(0, 100);
    if (mutation >= 99) //Big mutation
    {
        //Up to 20% change
        uint16_t newStrength = m_data.strength * Random::get().floatInRange(0.80, 1.20);
        PersonData child;
        child.isAlive   = true;
        child.colony    = m_data.colony;
        child.strength  = newStrength;
        return child;
    }
    else if (mutation >= 85)
    {
        //Up to 2% change
        uint16_t newStrength = m_data.strength * Random::get().floatInRange(0.98, 1.02);
        PersonData child;
        child.isAlive   = true;
        child.colony    = m_data.colony;
        child.strength  = newStrength;
        return child;
    }
    else
    {
        return m_data;
    }
}
