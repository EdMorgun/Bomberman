#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "unit.h"
#include "bomb.h"
#include "QKeyEvent"
#include "QPainter"
#include "vector"

class Bomberman : public Unit
{

public:
    Bomberman(int x, int y);
    ~Bomberman();
    void reactionForKeys(QKeyEvent *event, std::vector<PhysicalObject*> balloons);
    void reactionForReleaseKeys(QKeyEvent *event);
    bool frameBomber(int **cells, int bXDoors, int bYDoors, int bXBonus, int bYBonus, int bonus);
    std::vector<PhysicalUnit*> getBomb();
    std::vector<Bomb*> getBombs();

    void checkEnemy(PhysicalUnit *balloon);
    void takeBonus(int bouns);

    void setBomb(std::vector<PhysicalObject*> balloons);
    bool getStop();
    bool getBombSet();
    int getPower();

private:
    void checkVector();
    void checkKey(int key);
    bool checkBonus(int bXBonus, int bYBonus);
    bool death();
    std::vector<Bomb*> bombs;
    int lastVector, key, lastKey, power, countBomb, bombsSet;
    bool stop, bombSet;

};

#endif // BOMBERMAN_H
