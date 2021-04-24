#include "Person.h"

#include <iostream>

#include "../Util/Random.h"

void Person::init(const ChildData& data)
{

    m_strength = data.strength;
    m_colony = data.colony;
    m_isDiseased = data.isDiseased;
    m_isAlive = true;
    m_isSwimming = false;
    m_age = 0;
    m_productionCount = 0;
    m_stopSwimCount = 0;
}

void Person::startSwim(Vect2 dir)
{
    m_swimDir = dir;
    m_isSwimming = true;
}

void Person::endSwim()
{
    if (m_stopSwimCount++ > 10) {
        m_stopSwimCount = 0;
        m_isSwimming = false;
    }
}

void Person::turnAround()
{
    m_swimDir.x *= -1;
    m_swimDir.y *= -1;
}

void Person::update()
{
    m_age++;
    m_productionCount++;

    if (m_age > m_strength) {
        kill();
    }

    if (m_isDiseased) {
        m_age *= 1.5;
    }
}

void Person::fight(Person& other)
{
    if (other.m_colony == 0)
        return;

    if (other.m_strength >= m_strength) {
        kill();
    }
    else {
        other.kill();
    }
}

Vect2 Person::getNextMove() const
{
    if (m_isSwimming)
        return m_swimDir;
    else
        return {(int8_t)Random::get().intInRange(-1, 1),
                (int8_t)Random::get().intInRange(-1, 1)};
}

void Person::kill()
{
    m_age = 0;
    m_strength = 0;
    m_colony = 0;
    m_productionCount = 0;
    m_stopSwimCount = 0;

    m_isDiseased = false;
    m_isAlive = false;
    m_isSwimming = false;
}

void Person::giveDisease()
{
    m_isDiseased = true;
}

ChildData Person::getChild()
{
    m_productionCount = 0;

    ChildData child;
    child.colony = m_colony;
    child.strength = m_strength;

    // chance the child is cured of disease
    if (m_isDiseased) {
        child.isDiseased = Random::get().intInRange(0, 100) >= 85;
    }

    // Chance of the child getting a mutated strength value
    int mutation = Random::get().intInRange(0, 1000000);
    if (mutation >= 999'000) {
        child.isDiseased = true;
        child.strength *= 0.65;
    }
    else if (mutation >= 750'000) // Small mutation
    {
        child.strength *= Random::get().floatInRange(0.0, 1);
    }

    return child;
}
