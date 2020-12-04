#ifndef DOORSOPPENED_H
#define DOORSOPPENED_H

#include "state.h"
#include "doors.h"

class DoorsOppened: public State
{
public:
    void close(Doors* d) override final;
    void open(Doors*) override {}
};

#endif // DOORSOPPENED_H

