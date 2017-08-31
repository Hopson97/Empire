#include "Person.h"

#include "../Util/Random.h"

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
    int mutation = Random::get().intInRange(0, 1000000);
    if (mutation >= 999'965) //rekt
    {
        child.isDiseased = true;
        if (child.strength > 0)
        child.strength *= 0.65;
    }
    else if (mutation >= 960'000) //Big mutation
    {
        child.strength *= Random::get().floatInRange(0.90, 1.8);
    }
    else if (mutation >= 750'000) //Small mutation
    {
        child.strength  *= Random::get().floatInRange(0.95, 1.4);
    }

    return child;
}
