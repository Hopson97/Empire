#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <cstdint>
#include <vector>
#include <SFML/System/Vector2.hpp>

struct Vect2
{
    int8_t x : 2;
    int8_t y : 2;
};

//Simply, this is a struct for new people aka "children"
struct ChildData
{
    uint16_t strength;
    uint16_t colony;
    uint16_t isDiseased;
};

//Represents one person on the map
class Person
{
    public:
        void init   (const ChildData& data);

        void update();

        void startSwim(Vect2 dir);
        void endSwim();
        void turnAround();

        void kill();
        void giveDisease();
        void fight(Person& other);

        Vect2 getNextMove() const;

        ChildData getChild();

        uint16_t  getStrength   ()  const   { return m_strength;        }
        uint16_t  getColony     ()  const   { return m_colony;          }
        uint8_t getProduction   ()  const   { return m_productionCount; }
        bool    isAlive         ()  const   { return m_isAlive;         }
        bool    isDiseased      ()  const   { return m_isDiseased;      }
        bool    isSwimming      ()  const   { return m_isSwimming;      }

    private:
        uint16_t    m_age               = 0;
        uint16_t    m_strength          = 0;
        uint16_t    m_colony            = 0;
        uint8_t     m_productionCount   = 0;
        uint8_t     m_stopSwimCount     = 0;
        Vect2       m_swimDir;

        bool    m_isDiseased    : 1;
        bool    m_isAlive       : 1;
        bool    m_isSwimming    : 1;
};



#endif // PERSON_H_INCLUDED
