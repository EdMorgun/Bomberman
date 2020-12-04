#include "unit.h"
#include "iostream"
#include "fstream"

#include "QImage"
#include "QPainter"
#include "QDebug"

#include "physicalobject.h"

using namespace std;

enum {
    GRASS = 1,
    WALL = 2,
    STONE = 3,

    FramesToChangeAnim = 4,
    FirstAnim = 0,
    LastAnim = 4,
    LastAnimDeath = 8,
    DieAnim = 5,
    DeathVector = 5,
};

extern int SIZE;

Unit::Unit(int x, int y) : PhysicalUnit (x, y), destroyed(false)
{

}

void Unit::frame()
{
    frames++;
    if(frames == FramesToChangeAnim)
    {
        frames = -1;
        stepAnim++;
    }

    if(!dead) if(stepAnim == LastAnim) stepAnim = FirstAnim;

    if(dead)
    {
        if(stepAnim == LastAnimDeath)
        {
            destroyed = true;
            qDebug() << destroyed;
        }
    }
}

void Unit::frame(int **cells)
{
    frames++;
    if(frames == FramesToChangeAnim)
    {
        frames = -1;
        stepAnim++;
    }

    if(!dead)
    {
        move();
        if(checkCollision(cells)) comeBack();
        if(stepAnim == LastAnim) stepAnim = FirstAnim;
    }

    if(dead)
    {
        if(stepAnim == LastAnimDeath) destroyed = true;
    }
}

void Unit::frame(int **cells, std::vector<PhysicalUnit*> bombs)
{
    frames++;
    if(frames == FramesToChangeAnim)
    {
        frames = -1;
        stepAnim++;
    }

    if(!dead)
    {
        move();
        if(checkCollision(cells)) comeBack();
        for(std::vector<PhysicalUnit*>::iterator bomb = bombs.begin(); bomb < bombs.end(); bomb++)
        if(checkCollision(*bomb)) comeBack();
        if(stepAnim == LastAnim) stepAnim = FirstAnim;
    }

    if(dead)
    {
        if(stepAnim == LastAnimDeath) destroyed = true;
    }
}

void Unit::Dead()
{
    dead = true;
    frames = -1;
    stepAnim = 0;
    vector = DieAnim;
}

bool Unit::getDestroyed()
{
    return destroyed;
}

Unit::~Unit()
{

}
