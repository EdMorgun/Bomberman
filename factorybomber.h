#ifndef FACTORYBOMBER_H
#define FACTORYBOMBER_H

#include "factory.h"
#include "bomberman.h"

class FactoryBomberman : public Factory
{
public:
    Bomberman* createUnit(int x, int y) override;
   // Bomberman* createBomber(int x, int y);

};

#endif // FACTORYBOMBER_H
