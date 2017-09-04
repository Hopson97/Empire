#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <cstdint>
#include <vector>
#include <SFML/System/Vector2.hpp>

using vect_t = sf::Vector2<int8_t>;
using data_t = uint16_t;

//Simply, this is a struct for new people aka "children"
struct ChildData
{
    data_t strength;
    data_t colony;
    data_t isDiseased;
};

//Represents one person on the map
class Person
{
    public:
        void init   (const ChildData& data);

        void update();

        void startSwim(vect_t dir);
        void endSwim();
        void turnAround();

        void kill();
        void giveDisease();
        void fight(Person& other);

        vect_t getNextMove() const;

        ChildData getChild();

        data_t  getStrength     ()  const   { return m_strength;        }
        data_t  getColony       ()  const   { return m_colony;          }
        uint8_t getProduction   ()  const   { return m_productionCount; }
        bool    isAlive         ()  const   { return m_isAlive;         }
        bool    isDiseased      ()  const   { return m_isDiseased;      }
        bool    isSwimming      ()  const   { return m_isSwimming;      }

    private:
        vect_t m_swimDir;

        uint16_t    m_age               = 0;
        uint16_t    m_strength          = 0;
        uint16_t    m_colony            = 0;
        uint8_t     m_productionCount   = 0;
        uint8_t     m_stopSwimCount     = 0;

        bool    m_isDiseased    : 1;
        bool    m_isAlive       : 1;
        bool    m_isSwimming    : 1;
};



#endif // PERSON_H_INCLUDED
