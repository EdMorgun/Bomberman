#include "game.h"
#include "balloon.h"
#include "unit.h"

#include "QImage"
#include "QString"
#include "QPainter"
#include "QMessageBox"
#include"QDebug"

#include "vector"
#include "fstream"

using namespace std;

static int SIZE = 48;

enum
{
    GRASS = 1,
    WALL = 2,
    STONE = 3,
    DOORS = 4,
    BONUSPOWER = 5,
    BONUSBOMB = 6
};

Game::Game()
{
    grass.load(":/Images/1.png");
    wall.load(":/Images/2.png");
    stone.load(":/Images/3.png");
    doors.load(":/Images/4.png");
    bonusPower.load(":/Images/5.png");
    bonusBomb.load(":/Images/6.png");

    FB = std::unique_ptr<FactoryBalloon>(new FactoryBalloon());
    FBM = std::unique_ptr<FactoryBomberman>(new FactoryBomberman());

    loadGame();
}

void Game::loadMap(string filePath)
{
    ifstream stream(filePath);

    stream >> raw >> colons;
    cells = new int*[raw];
    for (int i = 0; i < raw; i++)
    {
        cells[i] = new int[colons];
    }

    for (int i = 0; i < raw; i++)
    {
        for (int j = 0; j < colons; j++)
        {
            int cell;
            stream >> cell;
            if(cell >= 4)
            {
                if(cell == DOORS)
                {
                    bXDoors = j;
                    bYDoors = i;
                }
                else if (cell > DOORS)
                {
                    bXBonus = j;
                    bYBonus = i;
                    bonus = cell;
                }
                cell = WALL;
            }
            cells[i][j] = cell;
        }
    }
}

void Game::paintMap(QPainter *painter, int cam)
{
    for (int i = 0; i < raw; i++)
    {
        for (int j = 0; j < colons; j++)
        {
            switch (cells[i][j])
            {
            case 1 :
                paint(j*SIZE, i*SIZE, painter, grass, cam);
                break;
            case 2:
                paint(j*SIZE, i*SIZE, painter, wall, cam);
                break;
            case 3:
                paint(j*SIZE, i*SIZE, painter, stone, cam);
                break;
            case 4:
                paint(j*SIZE, i*SIZE, painter, doors, cam);
                break;
            case 5:
                paint(j*SIZE, i*SIZE, painter, bonusPower, cam);
                break;
            case 6:
                paint(j*SIZE, i*SIZE, painter, bonusBomb, cam);
                break;
            }
        }
    }
}

void Game::paintGame(QPainter *painter)
{
    if(bomber->getX() >= SIZE*8) cam =  bomber->getX() - SIZE*8;
    if(cam > (colons-16)*SIZE) cam = SIZE*(colons-16);

    paintMap(painter, cam);

    if(bomber->getBombSet())
        for(Bomb* bomb : bomber->getBombs())
            (*bomb).paintBomb(painter, cam);

    for (Balloon *balloon : balloons)
        balloon->paint(balloon->getX(), balloon->getY(), painter, cam, balloon->getVector());

    bomber->paint(bomber->getX(), bomber->getY(), painter, cam, bomber->getVector());
}

void Game::spawnEnemies(int numberOfBallons)
{
    srand(static_cast<uint>(time(nullptr)));
    int balloons = 0;
    while(balloons < numberOfBallons)
    {
        for(int i = 0; i < raw; i++)
        {
            if(balloons == numberOfBallons) continue;
            for(int j = colons/2; j < colons; j++)
            {
                if(balloons == numberOfBallons) continue;
                if(cells[i][j] == 1)
                {
                    int r = rand() % 100;
                    if(r > 95)
                    {
                        this->balloons.push_back(FB->createUnit(j*SIZE, i*SIZE));
                        balloons++;
                    }
                }
            }
        }
    }
}

void Game::reactionForPressKeys(QKeyEvent *event)
{
    bomber->reactionForKeys(event, std::vector<PhysicalObject*>(balloons.begin(), balloons.end()));
}

void Game::reactionForReleaseKeys(QKeyEvent *event)
{
    bomber->reactionForReleaseKeys(event);
}

void Game::frame()
{
    for (std::vector<Balloon*>::iterator balloon = balloons.begin(); balloon < balloons.end(); balloon++)
    {
        (*balloon)->frameBalloon(&*bomber, cells);
        if((*balloon)->getDestroyed())
        {
            delete *balloon;
            balloons.erase(balloon);
        }
    }

    if(win == false) loose = bomber->frameBomber(cells, bXDoors, bYDoors, bXBonus, bYBonus, bonus);
    if(checkBonus(&*bomber)) bomber->takeBonus(bonus);
    win = checkWin();

    if(win == false) loose = bomber->frameBomber(cells, bXDoors, bYDoors, bXBonus, bYBonus, bonus);
    if(checkBonus(&*bomber)) bomber->takeBonus(bonus);
    win = checkWin();

    if(win || loose) end = true;

    checkDestoyedBalloons();
}

bool Game::checkBonus(PhysicalObject *bomber)
{
    int bX = bomber->getX() / SIZE;
    int bY = bomber->getY() / SIZE;
    int rX = bomber->getX() % SIZE;
    int rY = bomber->getY() % SIZE;

    if(bX == bXBonus && bY == bYBonus && rX == 0 && rY == 0)
    {
        cells[bYBonus][bXBonus] = GRASS;
        bXBonus = 0; bYBonus = 0;
        return true;
    }
    return false;
}

void Game::checkDestoyedBalloons()
{
    if(balloons.empty()) door->open();

}

bool Game::checkWin()
{
    int bX = bomber->getX() / SIZE;
    int bY = bomber->getY() / SIZE;
    int rX = bomber->getX() % SIZE;
    int rY = bomber->getY() % SIZE;

    if(bX == bXDoors && bY == bYDoors && rX == 0 && rY == 0 && !door->getDoorState()) return true;
    return false;
}

int Game::getResultGame()
{
    if(win) return 1;
    if(loose) return 2;
    return 0;
}

bool Game::getEnd()
{
    return end;
}

void Game::newGame()
{
    for(int i = 0; i < raw; i++)
        delete cells[i];

    delete cells;

    delete door;

    while(!balloons.empty())
        for(std::vector<Balloon*>::iterator balloon = balloons.begin(); balloon < balloons.end(); balloon++)
        {
            delete *balloon;
            balloons.erase(balloon);
        }

    loadGame();
}

void Game::loadGame()
{
    win = false; loose = false; end = false; cam = 0; allBalloonsDestroyed = false;

    door = new Doors();

    loadMap("D:/OOP/Labs/Levels/level1.txt");
    spawnEnemies(5);

    bomber = std::unique_ptr<Bomberman>(FBM->createUnit(SIZE, SIZE));
}

Game::~Game()
{
    for(int i = 0; i < raw; i++)
        delete cells[i];

    delete cells;

    if(!balloons.empty())
        for(std::vector<Balloon*>::iterator balloon = balloons.begin(); balloon < balloons.end(); balloon++)
        {
            delete *balloon;
            balloons.erase(balloon);
        }

    delete door;
}
