#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <cstdint>
#include <vector>

struct
#ifdef __GNUC__
__attribute__((packed, aligned(4)))
#endif // __GNUC__
PersonData
{
    unsigned    age             = 0;
    unsigned    strength        = 0;
    unsigned    colony          = 0;
    unsigned    productionCount = 0;
    bool    isDiseased      = false;
    bool    isAlive         = false;
};

class Person
{
    public:
        Person      () = default;
        void init   (const PersonData& data);

        void update();

        void kill();
        void giveDisease();
        void fight(Person& other);

        PersonData getChild();

        const PersonData& getData() const { return m_data; }

    private:
        PersonData m_data;
};



#endif // PERSON_H_INCLUDED
