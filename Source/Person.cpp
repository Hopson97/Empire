#include "Person.h"

Person::Person(const PersonData& data)
:   m_data  (data)
{
}

void Person::init(const PersonData& data)
{
    m_data = data;
}

void Person::update()
{
    m_data.age++;
}

