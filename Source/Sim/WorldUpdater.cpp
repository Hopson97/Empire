#include "WorldUpdater.h"

#include "Person.h"
#include "Map.h"

WorldUpdater::WorldUpdater(const Map& map)
:   m_pMap  (&map)
{ }

void WorldUpdater::updatePerson(Person& personUpdating,
                                Person& personMovingTo,
                                unsigned x, unsigned y,
                                unsigned xMoveTo, unsigned yMoveTo)
{

}
