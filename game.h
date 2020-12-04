#ifndef GAME_H
#define GAME_H

#include "QImage"
#include "QKeyEvent"

#include "factoryballoon.h"
#include "factorybomber.h"
#include "bomberman.h"
#include "balloon.h"
#include "doors.h"

#include "iostream"
#include "vector"
#include "memory"


class Game : DrawUnit
{

public:

    void loadMap(std::string filePath);
    void loadGame();
    void paintMap(QPainter *painter, int cam);
    void paintGame(QPainter *painter);
    void reactionForPressKeys(QKeyEvent *event);
    void reactionForReleaseKeys(QKeyEvent *event);
    void spawnEnemies(int numberOfBallons);
    void destroyWalls(PhysicalObject *bomb, int power);
    bool checkBonus(PhysicalObject *bomber);
    int getResultGame();
    bool getEnd();
    void frame();
    void bomberMove();
    void checkDestoyedBalloons();
    void newGame();

    static Game* getInstance()
    {
       static Game instance;
       return &instance;
    }

protected:

private:
    Game();
    ~Game();
    Game(const Game&);
    Game& operator=( Game& );

    Doors *door;
    bool checkWin();
    std::vector<Balloon*> balloons;
    bool allBalloonsDestroyed, win, loose, end;
    int** cells;
    int raw, colons, bXDoors, bYDoors, bonus, bXBonus, bYBonus, cam;
    QImage stone, grass, wall, doors, bonusPower, bonusBomb;
    std::unique_ptr<Bomberman> bomber;
    std::unique_ptr<FactoryBomberman> FBM;
    std::unique_ptr<FactoryBalloon> FB;
};

#endif // GAME_H
