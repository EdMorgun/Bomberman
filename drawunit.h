#ifndef DRAWUNIT_H
#define DRAWUNIT_H

#include "drawableobject.h"

class DrawUnit : public DrawableObject
{
public:
    DrawUnit();
    void paint(int x, int y, QPainter *painter, QImage image, int cam) override final;
    void paint(int x, int y, QPainter *painter, int cam, int vector) override final;
    int getFrames();
    int getStepAnim();

protected:
    QImage image;
    int frames, stepAnim;
};

#endif // DRAWUNIT_H
