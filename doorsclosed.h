#ifndef DOORSCLOSED_H
#define DOORSCLOSED_H

#include "state.h"
#include "doors.h"

class DoorsClosed: public State
{
public:
    void open(Doors* d) override final;
    void close(Doors* ) override {}
};

#endif // DOORSCLOSED_H
