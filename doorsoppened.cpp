#include "doorsclosed.h"
#include "doorsoppened.h"

void DoorsOppened::close(Doors *d)
{
    d->setDoorState(true);
    d->setState(new DoorsClosed());
    delete this;
}

