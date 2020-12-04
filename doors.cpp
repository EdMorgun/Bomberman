#include "doors.h"
#include "doorsclosed.h"
#include "doorsoppened.h"

Doors::Doors()
{
    state = new DoorsClosed();
    m_close = true;
}

void Doors::open()
{
    state->open(this);
}

void Doors::close()
{
    state->close(this);
}

void Doors::setState(State *s)
{
    this->state = s;
}

bool Doors::getDoorState()
{
    return m_close;
}

void Doors::setDoorState(bool st)
{
    m_close = st;
}

//void Doors::changeState() {
//    this->state->next(this);
//}



