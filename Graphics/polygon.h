#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include "line.h"

typedef QPair<QPoint, QPoint> Edge;

class Polygon : public Shape
{
public:
    Polygon();
    void AddVertex(QPoint newVertex);
    void ChangeLastVertex(QPoint vertex);
    void Move(QPoint pos);
    void Draw(QImage &img);
    void Fill(QImage &img);
    QList<Edge> Edges();
    QRect GetRect();
    bool isConvex();
protected:
    QList<QPoint> vertexs;
    void ClipToPolygon(QImage &img);
    void DrawTexturedHLine(int x0, int x1, int y, int h, int j, QImage &img);

};

#endif // POLYGON_H
