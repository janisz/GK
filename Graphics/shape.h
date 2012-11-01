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
    void SetColor(QColor color);
    QColor GetColor();
    virtual QRect GetRect() = 0;
    virtual void Draw(QImage &img) = 0;
    virtual void Move(int x, int y) = 0;
protected:
    QColor color;
};

#endif // SHAPE_H
