#ifndef FACTORYBALLOON_H
#define FACTORYBALLOON_H

#include "factory.h"
#include "balloon.h"

class FactoryBalloon : public Factory
{
public:
    Balloon* createUnit(int x, int y) override;
};

#endif // FACTORYBALLOON_H
