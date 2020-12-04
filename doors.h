#ifndef DOORS_H
#define DOORS_H

#include "state.h"

class Doors
{
public:
    Doors();
    void setState(State *s);
    bool getDoorState();
    void setDoorState(bool);
    void open();
    void close();
protected:
    State *state;
    bool m_close;
};

#endif // DOORS_H
