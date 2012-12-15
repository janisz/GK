#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include "line.h"
#include "QPoint"

class Rectangle : public Shape
{
public:
    Rectangle() {}
    Rectangle(QRect r);
    QRect GetRect() {return rect; }
    void Draw(QImage &img);
    void Move(QPoint pos);
    void ClipToPolygon(QImage &img) {  }
private:
    QRect rect;
};

#endif // RECTANGLE_H
