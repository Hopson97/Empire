#include "Person.h"

#include "../Util/Random.h"

void Person::init(const ChildData& data)
{
    m_strength      = data.strength;
    m_colony        = data.colony;
    m_isDiseased    = data.isDiseased;
    m_isAlive       = true;
}

void Person::update()
{
    m_age++;
    m_productionCount++;

    if (m_age > m_strength)
    {
        kill();
    }

    if (m_isDiseased)
    {
        m_age *= 1.5;
    }
}

void Person::fight(Person& other)
{
    if (other.m_colony == 0)
        return;

    if (other.m_strength >= m_strength)
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
    m_age        = 0;
    m_strength   = 0;
    m_colony     = 0;
    m_productionCount  = 0;

    m_isDiseased = false;
    m_isAlive    = false;
}

void Person::giveDisease()
{
    m_isDiseased = true;
}

ChildData Person::getChild()
{
    m_productionCount = 0;

    ChildData child;
    child.colony    = m_colony;
    child.strength  = m_strength;

    //chance the child is cured of disease
    if (m_isDiseased)
    {
        child.isDiseased = Random::get().intInRange(0, 100) >= 85;
    }

    //Chance of the child getting a mutated strength value
    int mutation = Random::get().intInRange(0, 1000000);
    if (mutation >= 999'000)
    {
        child.isDiseased = true;
        child.strength *= 0.65;
    }
    else if (mutation >= 800'000) //Small mutation
    {
        child.strength  *= Random::get().floatInRange(0.1, 1);
    }

    return child;
}
