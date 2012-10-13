#ifndef SHAPE_H
#define SHAPE_H

#include <QList>
#include <QPoint>
#include <QColor>
#include <QRect>

typedef QList<QPoint> QPointList;

class Shape
{
public:
    Shape();
    Shape(QColor color);
    Shape(QList<QPoint> points, QColor color);
    void SetPoints(QList<QPoint> points);
    void SetColor(QColor color);
    QList<QPoint> GetPoints();
    QColor GetColor();
    QRect GetRect();
private:
    QList<QPoint> pointList;
    QRect rect;
    QColor color;
    void setRect();

};

#endif // SHAPE_H
