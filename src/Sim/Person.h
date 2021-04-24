#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <vector>

struct Vect2 {
    int8_t x : 2;
    int8_t y : 2;
};

// Simply, this is a struct for new people aka "children"
struct ChildData {
    uint16_t strength;
    uint16_t colony;
    uint16_t isDiseased;
};

// Represents one person on the map
struct Person {
    void init(const ChildData& data);

    void update();

    void startSwim(Vect2 dir);
    void endSwim();
    void turnAround();

    void kill();
    void giveDisease();
    void fight(Person& other);

    Vect2 getNextMove() const;

    ChildData getChild();

    uint16_t age = 0;
    uint16_t strength = 0;
    uint16_t colony = 0;
    uint8_t productionCount = 0;
    uint8_t stopSwimCount = 0;
    Vect2 swimDir;

    bool isDiseased : 1;
    bool isAlive : 1;
    bool isSwimming : 1;
};

#endif // PERSON_H_INCLUDED
