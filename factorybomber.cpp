#include "factorybomber.h"

Bomberman* FactoryBomberman::createUnit(int x, int y)
{
    return new Bomberman(x, y);
}
