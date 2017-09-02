#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <cstdint>

struct
#ifdef __GNUC__
__attribute__((packed, aligned(4)))
#endif // __GNUC__
PersonData
{
    uint16_t    age             = 0;
    uint16_t    strength        = 0;
    uint8_t     colony          = 0;
    uint8_t     productionCount = 0;
    uint8_t     isDiseased      = false;
    uint8_t     isAlive         = false;
};

class Person
{
    public:
        Person      () = default;
        Person      (const PersonData& data);
        void init   (const PersonData& data);

        void update();

        void kill();
        void giveDisease();
        void fight(Person& other);

        PersonData getChild();

        const PersonData& getData() const { return m_data; }

        Person& operator=(const PersonData& data) { init(data); return *this; }

    private:
        PersonData m_data;
};

#endif // PERSON_H_INCLUDED
