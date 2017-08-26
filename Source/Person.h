#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <cstdint>

constexpr unsigned REPRODUCE_THRESHOLD = 12;

struct PersonData
{
    uint32_t    age             = 0;
    uint32_t    strength        = 0;

    uint8_t colony          = 0;
    uint8_t isAlive         = false;
    uint8_t productionCount = 0;
    uint8_t isDiseased      = 0;
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

    private:
        PersonData m_data;
};

#endif // PERSON_H_INCLUDED
