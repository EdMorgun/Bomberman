#ifndef BOMB_H
#define BOMB_H

#include "unit.h"
#include "QRect"
#include "explosionarea.h"

class Bomb : public Unit
{

public:
    Bomb(int x, int y, int power);
    ~Bomb();
    void paintBomb(QPainter *painter, int cam);
    void bombGo();
    bool getBoom();
    int getPower();

    void checkExplosionStone(int **cells, int bXDoors, int bYDoors, int bXBonus, int bYBonus, int bonus);
    void checkExplosion(Unit *unit);

private:
    ExplosionArea area;

    int tenTick, power;
    bool boom, checkedStone;
    bool leftWall, topWall, rightWall, downWall;

};

#endif // BOMB_H
