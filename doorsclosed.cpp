#include "doorsclosed.h"
#include "doorsoppened.h"

void DoorsClosed::open(Doors *d)
{
    d->setDoorState(false);
    d->setState(new DoorsOppened());
    delete this;
}

