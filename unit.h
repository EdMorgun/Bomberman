#ifndef UNIT_H
#define UNIT_H

#include <QImage>
#include <QString>

#include "physicalunit.h"
#include "drawunit.h"

class Unit : public PhysicalUnit, public DrawUnit
{

public:
    Unit(int x, int y);
    ~Unit();

    void frame();
    void frame(int **cells);
    void frame(int **cells, std::vector<PhysicalUnit*> bombs);

    bool getDestroyed();
    void Dead();
    
protected:
    bool destroyed;

};

#endif // UNIT_H
