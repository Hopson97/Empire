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
    m_data.productionCount++;

    if (m_data.age > m_data.strength)
    {
        kill();
    }
}

void Person::fight(Person& other)
{
    if (other.getData().strength >= getData().strength)
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
    m_data.productionCount = 0;

    //Chance of the child getting a mutated strength value
    int mutation = Random::get().intInRange(0, 1000);
    if (mutation >= 995) //Big mutation
    {
        uint16_t newStrength = m_data.strength * Random::get().floatInRange(0.93, 1.20);
        PersonData child;
        child.isAlive   = true;
        child.colony    = m_data.colony;
        child.strength  = newStrength;
        return child;
    }
    else if (mutation >= 975) //Small mutation
    {
        uint16_t newStrength = m_data.strength * Random::get().floatInRange(0.98, 1.05);
        PersonData child;
        child.isAlive   = true;
        child.colony    = m_data.colony;
        child.strength  = newStrength;
        return child;
    }
    else
    {
        PersonData child;
        child.isAlive   = true;
        child.colony    = m_data.colony;
        child.strength  = m_data.strength;
        return child;
    }
}
