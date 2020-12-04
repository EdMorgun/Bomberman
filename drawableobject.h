#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "QPainter"

class DrawableObject
{
public:
    void virtual paint(int x, int y, QPainter *painter, QImage image, int cam) = 0;
    void virtual paint(int x, int y, QPainter *painter, int cam, int vector) = 0;
    virtual ~DrawableObject() = default;

};

#endif // DRAWABLEOBJECT_H
