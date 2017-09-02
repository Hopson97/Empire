#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <cstdint>
#include <vector>
#include <SFML/System/Vector2.hpp>

using data_t        =   uint16_t;
using MoveVector    =   sf::Vector2<int8_t>;

class Person;

enum class MoveState : uint8_t
{
    Walking,
    Swimming,
};
//Simply, this is a struct for new people aka "children"
struct ChildData
{
    data_t strength;
    data_t colony;
    data_t isDiseased;

    operator Person() const;
};

//Represents one person on the map
class Person
{
    public:
        Person& init   (const ChildData& data);

        void update();

        void startSwim(const MoveVector& dir);
        void endSwim();

        void kill();
        void giveDisease();
        void fight(Person& other);

        MoveVector getNextMove() const;

        ChildData getChild();

        data_t getAge       ()  const   { return m_age;             }
        data_t getStrength  ()  const   { return m_strength;        }
        data_t getProduction()  const   { return m_productionCount; }
        data_t getColony    ()  const   { return m_colony;          }
        data_t getKills     ()  const   { return m_kills;           }
        bool   isAlive      ()  const   { return m_isAlive;         }
        bool   isDiseased   ()  const   { return m_isDiseased;      }

        void setAge         (data_t age)    { m_age = age;              }
        void setStrength    (data_t str)    { m_strength = str;         }
        void setProduction  (data_t pro)    { m_productionCount = pro;  }
        void setKills       (data_t kil)    { m_kills = kil;            }

        Person& operator=(const ChildData& data) { return init(data); }

        MoveState getMoveState  () const { return m_moveState; }

    private:
        data_t  m_age        = 0;
        data_t  m_strength   = 0;
        data_t  m_colony     = 0;
        data_t  m_productionCount  = 0;
        data_t  m_kills = 0;

        MoveVector m_swimVector;

        MoveState m_moveState = MoveState::Walking;

        bool    m_isDiseased = false;
        bool    m_isAlive    = false;


};



#endif // PERSON_H_INCLUDED
