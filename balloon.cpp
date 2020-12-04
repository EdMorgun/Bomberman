#include "balloon.h"
#include "random"
#include "QDebug"

static int SIZE = 48;

enum
{
    ToChangeAnimDie = 6,
    ToChangeAnim = 4,
    firstAnim = 0,
    lastAnim = 4,
    lastAnimDie = 5
};

Balloon::Balloon(int x, int y) : Unit (x, y), steps(0), coef(rand() % 4)
{
    image.load(":/Images/balloon.png");
}

void Balloon::changeVector()
{
    if(dead) return;
    std::mt19937 generator(static_cast<uint32_t>(time(nullptr)));
    std::uniform_int_distribution<int32_t> randomVector(1, 4);
    vector = static_cast<time_t>((randomVector(generator)) + static_cast<int>(coef));
    if(vector > 4) vector -= 4;

    steps = (rand() % SIZE/3 + SIZE/12 + coef) * 4;

    coef++;
    if(coef == 4) coef = 0;

    stone = false;
}

void Balloon::frameBalloon(Bomberman* bomber, int** cells)
{
    bomber->checkEnemy(this);
    checkSteps();
    if(this->getStone()) changeVector();
    if(bomber->getBombSet())
    {
        frame(cells, bomber->getBomb());
        for(Bomb* bomb : bomber->getBombs())
            if ((*bomb).getDead()) (*bomb).checkExplosion(this);
    }
    else frame(cells);
}

void Balloon::checkSteps()
{
    steps -= SIZE/16;
    if(steps == 0) changeVector();
}

Balloon* Balloon::getBalloon()
{
    return this;
}

bool Balloon::getDestroyed()
{
    return destroyed;
}

Balloon::~Balloon()
{

}
