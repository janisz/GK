#ifndef SHAPE_H
#define SHAPE_H

#include <QList>
#include <QPoint>
#include <QColor>
#include <QRect>
#include <QImage>
#include <QDebug>
#include "Globals.h"

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
    void SetType(Globals::ShapeType newType) { type = newType; }
    Globals::ShapeType GetType() { return type; }
    friend QDebug operator<< (QDebug d, const Shape *model);
protected:
    QColor color;
    Globals::ShapeType type;
};

inline QDebug operator<< (QDebug d, Shape* s) {
    d << s->GetType() << s->GetColor() << s->GetRect();
    return d;
}

#endif // SHAPE_H
