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
    Shape(QList<QPoint> points, QColor color, QList<int> alpha = QList<int>());
    void SetPoints(const QList<QPoint> points, QList<int> alpha = QList<int>());
    void SetColor(QColor color);
    QList<QPoint> GetPoints();
    QList<int> GetAlpha();
    QColor GetColor();
    QRect GetRect();
private:
    QList<QPoint> pointList;
    QList<int>  pointAplha;
    QRect rect;
    QColor color;
    void setRect();

};

#endif // SHAPE_H
