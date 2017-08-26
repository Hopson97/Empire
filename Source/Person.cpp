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
    if (other.getData().colony == 0) return;
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
    int mutation = Random::get().intInRange(0, 100);

    if (mutation >= 99) //Big mutation
    {
        uint16_t newStrength = m_data.strength * Random::get().floatInRange(0.90, 2.5);
        PersonData child;
        child.isAlive   = true;
        child.colony    = m_data.colony;
        child.strength  = newStrength;
        return child;
    }
    else if (mutation >= 85) //Small mutation
    {
        uint16_t newStrength = m_data.strength * Random::get().floatInRange(0.95, 1.5);
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
