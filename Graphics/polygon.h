#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include "line.h"

class Polygon : public Shape
{
public:
    Polygon();
    void AddVertex(QPoint newVertex);
    void Move(QPoint pos);
    void Draw(QImage &img);
    QRect GetRect();
protected:
    QList<QPoint> vertexs;

};

#endif // POLYGON_H
