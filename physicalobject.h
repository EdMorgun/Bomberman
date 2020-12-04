#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "vector"

class PhysicalObject
{
public:
    bool virtual checkCollision(int **cells) = 0;
    bool virtual checkCollision(PhysicalObject *bomb) = 0;
    int virtual getX() = 0;
    int virtual getY() = 0;
    virtual ~PhysicalObject() = default;

};

#endif // PHYSICALOBJECT_H
