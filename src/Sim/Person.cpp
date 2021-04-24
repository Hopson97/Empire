#include "Person.h"

#include <iostream>

#include "../Util/Random.h"

void Person::init(const ChildData& data)
{

    strength = data.strength;
    colony = data.colony;
    isDiseased = data.isDiseased;
    isAlive = true;
    isSwimming = false;
    age = 0;
    productionCount = 0;
    stopSwimCount = 0;
}

void Person::startSwim(Vect2 dir)
{
    swimDir = dir;
    isSwimming = true;
}

void Person::endSwim()
{
    if (stopSwimCount++ > 10) {
        stopSwimCount = 0;
        isSwimming = false;
    }
}

void Person::turnAround()
{
    swimDir.x *= -1;
    swimDir.y *= -1;
}

void Person::update()
{
    age++;
    productionCount++;

    if (age > strength) {
        kill();
    }

    if (isDiseased) {
        age *= 1.5;
    }
}

void Person::fight(Person& other)
{
    if (other.colony == 0)
        return;

    if (other.strength >= strength) {
        kill();
    }
    else {
        other.kill();
    }
}

Vect2 Person::getNextMove() const
{
    if (isSwimming)
        return swimDir;
    else
        return {(int8_t)Random::get().intInRange(-1, 1),
                (int8_t)Random::get().intInRange(-1, 1)};
}

void Person::kill()
{
    age = 0;
    strength = 0;
    colony = 0;
    productionCount = 0;
    stopSwimCount = 0;

    isDiseased = false;
    isAlive = false;
    isSwimming = false;
}

void Person::giveDisease()
{
    isDiseased = true;
}

ChildData Person::getChild()
{
    productionCount = 0;

    ChildData child;
    child.colony = colony;
    child.strength = strength;

    // chance the child is cured of disease
    if (isDiseased) {
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
