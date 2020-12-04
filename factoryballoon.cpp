#include "factoryballoon.h"

Balloon* FactoryBalloon::createUnit(int x, int y)
{
    return new Balloon(x, y);
}
