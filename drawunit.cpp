#include "drawunit.h"

static int STANDART_SIZE = 48;

extern int SIZE;

DrawUnit::DrawUnit() : frames(0), stepAnim(0)
{

}

void DrawUnit::paint(int x, int y, QPainter *painter, QImage image, int cam)
{
    if(x + STANDART_SIZE < cam || cam + STANDART_SIZE*15 < x - STANDART_SIZE) return;
    QRect q((x - cam)*SIZE/STANDART_SIZE, y*SIZE/STANDART_SIZE, SIZE, SIZE);
    painter->drawImage(q, image);
}

void DrawUnit::paint(int x, int y, QPainter *painter, int cam, int vector)
{
    if(x + STANDART_SIZE < cam || cam + STANDART_SIZE*15 < x - STANDART_SIZE) return;
    QRect q((x - cam)*SIZE/STANDART_SIZE, y*SIZE/STANDART_SIZE, SIZE, SIZE);
    painter->drawImage(q, image.copy(stepAnim*STANDART_SIZE, (vector-1)*STANDART_SIZE, STANDART_SIZE, STANDART_SIZE));
}

int DrawUnit::getFrames()
{
    return frames;
}

int DrawUnit::getStepAnim()
{
    return stepAnim;
}
