#include "Person.h"

#include "../Util/Random.h"

void Person::init(const ChildData& data)
{

    m_strength      = data.strength;
    m_colony        = data.colony;
    m_isDiseased    = data.isDiseased;
    m_isAlive       = true;
    m_age               = 0;
    m_productionCount   = 0;
    m_kills             = 0;
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
        m_kills++;
        other.kill();
    }
}

MoveVector Person::getNextMove() const
{
    return { Random::get().intInRange(-1, 1),
             Random::get().intInRange(-1, 1)};
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
    static const data_t KILL_THRESHOLD = 15;

    int killPoints = 0;
        //std::ceil(KILL_THRESHOLD / std::max((uint16_t)1, std::min(KILL_THRESHOLD, m_kills)));

    m_productionCount = 0;

    ChildData child;
    child.colony    = m_colony;
    child.strength  = m_strength + killPoints;

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
