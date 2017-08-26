#include "Person.h"

Person::Person(const PersonData& data)
:   m_data  (data)
{
    m_data.isAlive = true;
}

void Person::init(const PersonData& data)
{
    m_data = data;
    m_data.isAlive = true;
}

void Person::update()
{
    m_data.age++;
}

