#ifndef BALLOON_H
#define BALLOON_H

#include "unit.h"
#include "bomb.h"
#include "bomberman.h"

class Balloon : public Unit
{

public:
    Balloon(int x, int y);
    ~Balloon();

    void frameBalloon(Bomberman* bomber, int** cells);
    void changeVector();
    void checkSteps();
    bool getDestroyed();
    Balloon* getBalloon();

private:
    int steps, coef;

};

#endif // BALLOON_H
