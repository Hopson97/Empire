#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <cstdint>
#include <vector>

using data_t = uint16_t;

struct ChildData
{
    data_t strength;
    data_t colony;
    data_t isDiseased;
};

class Person
{
    public:
        void init   (const ChildData& data);

        void update();

        void kill();
        void giveDisease();
        void fight(Person& other);

        ChildData getChild();

        data_t getStrength  ()  const   { return m_strength;        }
        data_t getProduction()  const   { return m_productionCount; }
        data_t getColony    ()  const   { return m_colony;          }
        bool   isAlive      ()  const   { return m_isAlive;         }
        bool   isDiseased   ()  const   { return m_isDiseased;      }

    private:
        data_t  m_age        = 0;
        data_t  m_strength   = 0;
        data_t  m_colony     = 0;
        data_t  m_productionCount  = 0;
        data_t  m_kills = 0;

        bool    m_isDiseased = false;
        bool    m_isAlive    = false;
};



#endif // PERSON_H_INCLUDED
