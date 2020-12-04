#include "bomb.h"
#include "QPainter"
#include "QDebug"

static int SIZE = 48;

enum
{
    GRASS = 1,
    WALL = 2,
    STONE = 3,
    DOORS = 4,

    boomLeft = 2,
    boomTop = 3,
    boomRight = 4,
    boomDown = 5,
    boomCentre = 6,
    boomX = 7,
    boomY = 8,
    boomWall = 9,

    lastAnimExplosion = 7
};

Bomb::Bomb(int x, int y, int power) : Unit (x, y), tenTick(0), power(power), boom(false), checkedStone(false),
   leftWall(false), topWall(false), rightWall(false), downWall(false)
{
    area.Left = -1; area.Top = -1; area.Right = -1; area.Down = -1;
    image.load(":/Images/bomb.png");
}

void Bomb::bombGo()
{
    frame();

    if(!dead)
    {
        if(frames == -1) tenTick++;
        if(tenTick == 20 + power * 2 && !dead) Dead();
    }

    if(dead)
    {
        if(stepAnim == lastAnimExplosion) destroyed = true;
    }
}

void Bomb::paintBomb(QPainter *painter, int cam)
{
    paint(x, y, painter, cam, vector);

    if(dead)
    {
        paint(x, y, painter, cam, boomCentre);
        for(int i = 1; i <= power; i++)
        {
            if(leftWall && area.Left == i-1)
            {
                paint(x - SIZE*i, y, painter, cam, boomWall);
            }
            if(area.Left <= i-1 && area.Left != -1) continue;
            else
            {
                if(i < power) paint(x - SIZE*i, y, painter, cam, boomX);
                else paint(x - SIZE*i, y, painter, cam, boomLeft);
            }
        }
        for(int i = 1; i <= power; i++)
        {
            if(topWall && area.Top == i-1)
            {
                paint(x, y - SIZE*i, painter, cam, boomWall);
            }
            if(area.Top <= i-1 && area.Top != -1) continue;
            else
            {
                if(i < power) paint(x, y - SIZE*i, painter, cam, boomY);
                else paint(x, y - SIZE*i, painter, cam, boomTop);
            }
        }

        for(int i = 1; i <= power; i++)
        {
            if(rightWall && area.Right == i-1)
            {
                paint(x + SIZE*i, y, painter, cam, boomWall);
            }
            if(area.Right <= i-1 && area.Right != -1) continue;
            else
            {
                if(i < power) paint(x + SIZE*i, y, painter, cam, boomX);
                else paint(x + SIZE*i, y, painter, cam, boomRight);
            }
        }

        for(int i = 1; i <= power; i++)
        {
            if(downWall && area.Down == i-1)
            {
                paint(x, y + SIZE*i, painter, cam, boomWall);
            }
            if(area.Down <= i-1 && area.Down != -1) continue;
            else
            {
                if(i < power) paint(x, y + SIZE*i, painter, cam, boomY);
                else paint(x, y + SIZE*i, painter, cam, boomDown);
            }
        }
    }
}

void Bomb::checkExplosionStone(int **cells, int bXDoors, int bYDoors, int bXBonus, int bYBonus, int bonus)
{
    if (checkedStone) return;

    int bX = x / SIZE;
    int bY = y / SIZE;

    for(int i = 1; i <= power; i++)
    {
        if(area.Left >= 0) continue;
        if(cells[bY][bX-i] == STONE) area.Left = i-1;
        else
        if (cells[bY][bX-i] == WALL)
        {
            if (bX-i == bXDoors && bY == bYDoors)
            {
                area.Left = i-1;
                cells[bY][bX-i] = DOORS;
            }
            else if (bX-i == bXBonus && bY == bYBonus)
            {
                area.Left = i-1;
                cells[bY][bX-i] = bonus;
            }
            else
            {
                area.Left = i-1;
                cells[bY][bX-i] = GRASS;
                leftWall = true;
            }
        }
    }

    for(int i = 1; i <= power; i++)
    {
        if(area.Top >= 0) continue;
        if(cells[bY-i][bX] == STONE) area.Top = i-1;
        else
        if (cells[bY-i][bX] == WALL)
        {
            if (bX == bXDoors && bY-i == bYDoors)
            {
                area.Top = i-1;
                cells[bY-i][bX] = DOORS;
            }
            else if (bX == bXBonus && bY-i == bYBonus)
            {
                area.Top = i-1;
                cells[bY-i][bX] = bonus;
            }
            else
            {
                area.Top = i-1;
                cells[bY-i][bX] = GRASS;
                topWall = true;
            }
        }
    }

    for(int i = 1; i <= power; i++)
    {
        if(area.Right >= 0) continue;
        if(cells[bY][bX+i] == STONE) area.Right = i-1;
        else
        if (cells[bY][bX+i] == WALL)
        {
            if (bX+i == bXDoors && bY == bYDoors)
            {
                area.Right = i-1;
                cells[bY][bX+i] = DOORS;
            }
            else if (bX+i == bXBonus && bY == bYBonus)
            {
                area.Right = i-1;
                cells[bY][bX+i] = bonus;
            }
            else
            {
                area.Right = i-1;
                cells[bY][bX+i] = GRASS;
                rightWall = true;
            }
        }
    }

    for(int i = 1; i <= power; i++)
    {
        if(area.Down >= 0) continue;
        if(cells[bY+i][bX] == STONE) area.Down = i-1;
        else
        if (cells[bY+i][bX] == WALL)
        {
            if (bX == bXDoors && bY+i == bYDoors)
            {
                area.Down = i-1;
                cells[bY+i][bX] = DOORS;
            }
            else if (bX == bXBonus && bY+i == bYBonus)
            {
                area.Down = i-1;
                cells[bY+i][bX] = bonus;
            }
            else
            {
                area.Down = i-1;
                cells[bY+i][bX] = GRASS;
                downWall = true;
            }
        }
    }

    vector = boomCentre;

    checkedStone = true;
}

void Bomb::checkExplosion(Unit *unit)
{
    if(unit->getDead()) return;
    if(area.Left == -1) area.Left = power;
    if(area.Top == -1) area.Top = power;
    if(area.Right == -1) area.Right = power;
    if(area.Down == -1) area.Down = power;

    if((unit->getX() > x - area.Left*SIZE - SIZE/2 && unit->getX() < x + area.Right*SIZE + SIZE/2 &&
        unit->getY() >= y - SIZE/2 && unit->getY() <= y + SIZE/2 ) ||
            (unit->getX() >= x - SIZE/2 && unit->getX() <= x + SIZE/2 &&
             unit->getY() >= y - area.Top*SIZE - SIZE/2 && unit->getY() <= y + area.Down*SIZE + SIZE/2 ))
    {
        unit->Dead();
    }
}

int Bomb::getPower()
{
    return power;
}

bool Bomb::getBoom()
{
    return boom;
}

Bomb::~Bomb()
{

}
