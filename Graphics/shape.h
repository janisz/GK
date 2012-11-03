#ifndef SHAPE_H
#define SHAPE_H

#include <QList>
#include <QPoint>
#include <QColor>
#include <QRect>
#include <QImage>

typedef QList<QPoint> QPointList;

class Shape
{
public:
    //interface
    virtual QRect GetRect() = 0;
    virtual void Draw(QImage &img) = 0;
    virtual void Move(QPoint pos) = 0;
    //declaration
    void Move(int x, int y) { Move(QPoint(x, y)); }
    void SetColor(QColor color) { this->color = color; }
    QColor GetColor() { return color; }
protected:
    QColor color;
};

#endif // SHAPE_H
