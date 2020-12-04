#ifndef FACTORY_H
#define FACTORY_H

#include "unit.h"

class Factory
{
public:
    virtual Unit* createUnit(int x, int y) = 0;
    virtual ~Factory() = default;
};

#endif // FACTORY_H
