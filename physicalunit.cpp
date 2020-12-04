#include "physicalunit.h"

static int SIZE = 48;

enum {
    WALL = 2,
    STONE = 3,
};

PhysicalUnit::PhysicalUnit(int x, int y) : x(x), y(y),
    stone(false), dead(false), vector(1), step(SIZE/16)
{  

}

void PhysicalUnit::move()
{
    if(dead) return;
    switch (vector)
    {
    case 1:
        x -= step;
        break;
    case 2:
        y -= step;
        break;
    case 3:
        x += step;
        break;
    case 4:
        y += step;
        break;
    }
}

bool PhysicalUnit::checkCollision(int **cells)
{
    int bX = x / SIZE;
    int bY = y / SIZE;
    int rX = x % SIZE;
    int rY = y % SIZE;

    switch (vector)
    {
    case 1:
        if((rY <= SIZE/3*2 && (cells[bY][bX] == WALL || cells[bY][bX] == STONE))||
                (rY > SIZE/3 && rY < SIZE/3*2 && (cells[bY+1][bX] == WALL || cells[bY+1][bX] == STONE)) ||
                    (rY > SIZE/3*2 && (cells[bY+1][bX] == WALL || cells[bY+1][bX] == STONE)))
        {
            return true;
        }
        else if(rY > 0 && rY <= SIZE/2 && (cells[bY+1][bX] == WALL || cells[bY+1][bX]== STONE) &&
                (cells[bY][bX] != WALL || cells[bY][bX] != STONE))
        {
            y -= step;
            break;
        }
        else if(rY > SIZE/2 && (cells[bY][bX] == WALL || cells[bY][bX] == STONE) &&
                (cells[bY+1][bX] != WALL || cells[bY+1][bX] != STONE))
        {
            y += step;
            break;
        }
        break;

    case 2:
        if(((rX >= 0 && rX <= SIZE/2) && (cells[bY][bX] == WALL || cells[bY][bX] == STONE)) ||
                    (rX > SIZE/2 && (cells[bY][bX+1] == WALL || cells[bY][bX+1] == STONE)))
        {
            return true;
        }
        else if(rX > 0 && (cells[bY][bX+1] == WALL || cells[bY][bX+1] == STONE) &&
                (cells[bY][bX] != WALL || cells[bY][bX] != STONE))
        {
            x -= step;
            break;
        }
        else if(rX >= SIZE/2 && (cells[bY][bX] == WALL || cells[bY][bX] == STONE) &&
                (cells[bY][bX+1] != WALL || cells[bY][bX+1] != STONE))
        {
            x += step;
            break;
        }
        break;
    case 3:
        if(((rX > 0 && rY < SIZE/3*2) && (cells[bY][bX+1] == WALL || cells[bY][bX+1] == STONE)) ||
                (rY > SIZE/3 && rY < SIZE/3*2 && (cells[bY+1][bX+1] == WALL || cells[bY+1][bX+1] == STONE)) ||
                    (rY > SIZE/3*2 && (cells[bY+1][bX+1] == WALL || cells[bY+1][bX+1] == STONE)))
        {
            return true;
        }
        else if(rY > 0 && rY <= SIZE/2 && (cells[bY+1][bX+1] == WALL || cells[bY+1][bX+1] == STONE) &&
                (cells[bY][bX+1] != WALL || cells[bY][bX+1] != STONE))
        {
            y -= step;
            break;
        }
        else if(rY > SIZE/2 && (cells[bY][bX+1] == WALL || cells[bY][bX+1] == STONE) &&
                (cells[bY+1][bX+1] != WALL || cells[bY+1][bX+1] != STONE))
        {
            y += step;
            break;
        }
        break;
    case 4:
        if(((rX <= SIZE/2 && rY > 0) && (cells[bY+1][bX] == WALL || cells[bY+1][bX] == STONE)) ||
                    (rX > SIZE/2 && (cells[bY+1][bX+1] == WALL || cells[bY+1][bX+1] == STONE)))
        {
            return true;
        }
        else if(rX > 0 && rX <= SIZE/2 && (cells[bY+1][bX+1] == WALL || cells[bY+1][bX+1] == STONE) &&
                (cells[bY][bX] != WALL || cells[bY][bX] != STONE))
        {
            x -= step;
            break;
        }
        else if(rX >= SIZE/2 && (cells[bY+1][bX] == WALL || cells[bY+1][bX] == STONE) &&
                (cells[bY][bX+1] != WALL || cells[bY][bX+1] != STONE))
        {
            x += step;
            break;
        }
        break;
    }
    return false;
}

bool PhysicalUnit::checkCollision(PhysicalObject *bomb)
{
    switch (vector)
    {
    case 1:
        if(x + SIZE > bomb->getX() && x <= bomb->getX() + SIZE && bomb->getY() == y) return true;
        break;
    case 2:
        if(y + SIZE > bomb->getY() && y <= bomb->getY() + SIZE && bomb->getX() == x) return true;
        break;
    case 3:
        if(x + SIZE > bomb->getX() && x <= bomb->getX() + SIZE && bomb->getY() == y) return true;
        break;
    case 4:
        if(y + SIZE > bomb->getY() && y <= bomb->getY() + SIZE && bomb->getX() == x) return true;
        break;
    }
    return false;
}

bool PhysicalUnit::checkCollision(PhysicalUnit *unit)
{
    if(dead || unit->getDead()) return false;
    if(x - SIZE/2 <= unit->getX() && unit->getX() < x + SIZE/2 &&
        unit->getY() >= y - SIZE/2 && unit->getY() < y + SIZE/2) return true;
    return false;
}

void PhysicalUnit::comeBack()
{
    stone = true;
    switch (vector)
    {
    case 1:
        x += step;
        break;
    case 2:
        y += step;
        break;
    case 3:
        x -= step;
        break;
    case 4:
        y -= step;
        break;
    }
}

bool PhysicalUnit::getDead()
{
    return dead;
}

bool PhysicalUnit::getStone()
{
    return stone;
}

int PhysicalUnit::getX()
{
    return x;
}

int PhysicalUnit::getY()
{
    return y;
}

int PhysicalUnit::getVector()
{
    return vector;
}
