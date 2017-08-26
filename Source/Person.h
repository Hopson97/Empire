#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <cstdint>

struct PersonData
{
    uint16_t    isAlive     = false;
    uint16_t    colony      = 0;
    uint16_t    age         = 0;
    uint16_t    strength    = 0;
};

class Person
{
    public:
        Person      (const PersonData& data);
        void init   (const PersonData& data);

        void update();

        const PersonData& getData() const { return m_data; }

    private:
        PersonData m_data;
};

#endif // PERSON_H_INCLUDED
