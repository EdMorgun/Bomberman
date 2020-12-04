#ifndef PHYSICUNIT_H
#define PHYSICUNIT_H

#include "physicalobject.h"

class PhysicalUnit : public PhysicalObject
{
public:
    PhysicalUnit(int x, int y);
    bool checkCollision(int **cells) override final;
    bool checkCollision(PhysicalObject *bomb) override final;
    bool checkCollision(PhysicalUnit *object);
    int getX() override final;
    int getY() override final;

    int getVector();
    bool getStone();
    bool getDead();

    void comeBack();
    void move();

protected:
    int x, y;
    bool stone, dead;
    int vector, step;

};

#endif // PHYSICUNIT_H
