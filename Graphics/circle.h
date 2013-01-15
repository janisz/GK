#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
public:
    Circle() {}
    Circle(QPoint pos, int r, QColor c) { Centre = pos; Radius = r; lineColor = c;}
    QRect GetRect() { return QRect( Centre.x() - Radius, Centre.y() - Radius, Radius, Radius); }
    void Draw(QImage &img);
    void Move(QPoint pos) { Centre += pos; }
    void ClipToPolygon(QImage &img) { Draw(img); }
    QPoint Centre;
    int Radius;
};

#endif // CIRCLE_H
