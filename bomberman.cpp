#include "bomberman.h"
#include "bomb.h"

#include "vector"

#include "QPainter"
#include "QMessageBox"
#include "QDebug"
#include "QImage"
#include "QRect"

static int SIZE = 48;

enum {
    GRASS = 1,
    FirstAnim = 0,
    FramesToChangeAnim = 4,
    DeathVector = 5,
    LastAnimDeath = 8
};

Bomberman::Bomberman(int x, int y) : Unit (x, y), lastVector(0), key(0), lastKey(0),
    power(2), countBomb(1), bombsSet(0), stop(true), bombSet(false)
{
    image.load(":/Images/bomberman.png");
}

void Bomberman::checkEnemy(PhysicalUnit *balloon)
{
    if(checkCollision(balloon)) Dead();
}

void Bomberman::reactionForKeys(QKeyEvent *event, std::vector<PhysicalObject*> balloons)
{
    if(dead) return;

    if(event->key() != Qt::Key_Z) stop = false;

    switch (event->key())
    {

    case Qt::Key_Left:
        if (key != 1)
        {
            lastKey = key;
            key = 1;
        }
        break;

    case Qt::Key_Up:
        if (key != 2)
        {
            lastKey = key;
            key = 2;
        }
        break;

    case Qt::Key_Right:
        if (key != 3)
        {
            lastKey = key;
            key = 3;
        }
        break;

    case Qt::Key_Down:
        if (key != 4)
        {
            lastKey = key;
            key = 4;
        }
        break;

    case Qt::Key_Z:
        setBomb(balloons);
        break;

    default:
        stop = true;
        break;
    }
}

void Bomberman::reactionForReleaseKeys(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        checkKey(1);
        break;

    case Qt::Key_Up:
        checkKey(2);
        break;

    case Qt::Key_Right:
        checkKey(3);
        break;

    case Qt::Key_Down:
        checkKey(4);
        break;

    default:
        break;
    }
}

bool Bomberman::checkBonus(int bXBonus, int bYBonus)
{
    int bX = x / SIZE;
    int bY = y / SIZE;
    int rX = x % SIZE;
    int rY = y % SIZE;

    if(bX == bXBonus && bY == bYBonus && rX == 0 && rY == 0) return true;
    return false;
}

void Bomberman::takeBonus(int bonus)
{
    switch (bonus)
    {
    case 5:
        power++;
        break;
    case 6:
        countBomb++;
        break;
    }
}

void Bomberman::checkKey(int key)
{
    if(lastKey == key) lastKey = 0;
    else
    if(lastKey == 0 && this->key == key)
    {
        this->key = 0;
        stop = true;
    }
    else if(this->key == key)
    {
        this->key = lastKey;
        lastKey = 0;
    }
}

void Bomberman::setBomb(std::vector<PhysicalObject*> balloons)
{
    if(countBomb <= bombsSet) return;

    int bX = x / SIZE;
    int bY = y / SIZE;

    if (x % SIZE > SIZE/2) bX++;
    if (y % SIZE > SIZE/2) bY++;

    Bomb *bomb = new Bomb(bX*SIZE, bY*SIZE, power);

    bool canSet = true;

    for(std::vector<PhysicalObject*>::iterator balloon = balloons.begin(); balloon < balloons.end(); balloon++)
        if((*balloon)->checkCollision(bomb)) canSet = false;

    for(Bomb* bombb : bombs)
        if(bomb->getX() == bombb->getX() && bomb->getY() == bombb->getY()) canSet = false;

    if(canSet)
    {
        bombs.push_back(bomb);
        bombsSet++;
        bombSet = true;
    }
    else delete bomb;
}

bool Bomberman::frameBomber(int **cells, int bXDoors, int bYDoors, int bXBonus, int bYBonus, int bonus)
{
    if (!stop)
    {
        frame(cells);
        if(!dead)
        {
            if(stepAnim == FramesToChangeAnim || vector != lastVector) stepAnim = FirstAnim;
            lastVector = vector;
            if (key != 0) vector = key;
        }
    } 

    if(bombSet)
    {
        for(std::vector<Bomb*>::iterator bomb = bombs.begin(); bomb < bombs.end(); bomb++)
        {
            (*bomb)->bombGo();
            if ((*bomb)->getDead())
            {
                (*bomb)->checkExplosionStone(cells, bXDoors, bYDoors, bXBonus, bYBonus, bonus);
                (*bomb)->checkExplosion(this);
                for(Bomb* bombb : bombs)
                    (*bomb)->checkExplosion(bombb);
            }
            if ((*bomb)->getDestroyed())
            {
                delete *bomb;
                bombs.erase(bomb);
                bombsSet--;
                if(bombsSet == 0) bombSet = false;
            }
        }
    }

    if(dead)
    {
        return death();
    }

    return false;
}

std::vector<PhysicalUnit*> Bomberman::getBomb()
{
    return std::vector<PhysicalUnit*>(bombs.begin(), bombs.end());
}

std::vector<Bomb*> Bomberman::getBombs()
{
    return bombs;
}

bool Bomberman::getBombSet()
{
    return bombSet;
}

bool Bomberman::death()
{
    frames++;
    if(frames == FramesToChangeAnim)
    {
        frames = -1;
        stepAnim++;
    }

    if(stepAnim == LastAnimDeath) return true;

    return false;
}

int Bomberman::getPower()
{
    return power;
}

Bomberman::~Bomberman()
{
    if(!bombs.empty())
        for(std::vector<Bomb*>::iterator bomb = bombs.begin(); bomb < bombs.end(); bomb++)
        {
            delete *bomb;
            bombs.erase(bomb);
        }
}
