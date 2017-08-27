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

    if (m_data.isDiseased)
    {
        m_data.age *= 1.5;
    }
}

void Person::fight(Person& other)
{
    if (other.getData().colony == 0) return;
    if (other.getData().strength >= getData().strength)
    {
        kill();
    }
    else
    {
        other.kill();
    }
}

void Person::kill()
{
    m_data = PersonData();
}

void Person::giveDisease()
{
    m_data.isDiseased = true;
}

PersonData Person::getChild()
{
    m_data.productionCount = 0;

    PersonData child;
    child.isAlive   = true;
    child.colony    = m_data.colony;
    child.strength  = m_data.strength;

    //5% the child is cured of disease
    if (m_data.isDiseased)
    {
        child.isDiseased = Random::get().intInRange(0, 100) >= 85;
    }

    //Chance of the child getting a mutated strength value
    int mutation = Random::get().intInRange(0, 1000);
    if (mutation >= 999) //rekt
    {
        child.isDiseased = true;
        if (child.strength > 0)
        child.strength /= 2;
    }
    else if (mutation >= 960) //Big mutation
    {
        child.strength *= Random::get().floatInRange(0.90, 1.6);
    }
    else if (mutation >= 750) //Small mutation
    {
        child.strength  *= Random::get().floatInRange(0.95, 1.3);
    }

    return child;
}
