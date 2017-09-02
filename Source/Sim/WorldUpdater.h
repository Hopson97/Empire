#ifndef WORLDUPDATER_H_INCLUDED
#define WORLDUPDATER_H_INCLUDED

class Map;
class Person;

class WorldUpdater
{
    public:
        WorldUpdater(const Map& map);

        void updatePerson(Person& personUpdating,
                          Person& personMovingTo,
                          unsigned x, unsigned y,
                          unsigned xMoveTo, unsigned yMoveTo);

    private:
        const Map* m_pMap = nullptr;
};

#endif // WORLDUPDATER_H_INCLUDED
