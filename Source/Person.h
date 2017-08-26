#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

struct PersonData
{
    int     colony;
    int     age;
    int     strength;
    bool    isAlive = false;
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
