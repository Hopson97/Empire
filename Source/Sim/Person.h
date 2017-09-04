#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <cstdint>
#include <vector>
#include <SFML/System/Vector2.hpp>

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

        void startSwim(const sf::Vector2i& dir);
        void endSwim();
        void turnAround();

        void kill();
        void giveDisease();
        void fight(Person& other);

        sf::Vector2i getNextMove() const;

        ChildData getChild();

        data_t  getStrength     ()  const   { return m_strength;        }
        data_t  getProduction   ()  const   { return m_productionCount; }
        data_t  getColony       ()  const   { return m_colony;          }
        bool    isAlive         ()  const   { return m_isAlive;         }
        bool    isDiseased      ()  const   { return m_isDiseased;      }
        bool    isSwimming      ()  const   { return m_isSwimming;      }

    private:
        sf::Vector2i m_swimDir;

        data_t  m_age        = 0;
        data_t  m_strength   = 0;
        data_t  m_colony     = 0;
        data_t  m_productionCount  = 0;
        data_t  m_stopSwimCount = 0;

        bool    m_isDiseased = false;
        bool    m_isAlive    = false;
        bool    m_isSwimming = false;
};



#endif // PERSON_H_INCLUDED
