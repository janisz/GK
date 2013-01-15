#ifndef SHAPE_H
#define SHAPE_H

#include <QList>
#include <QPoint>
#include <QColor>
#include <QRect>
#include <QImage>
#include <QDebug>
#include "Globals.h"
class Polygon;
typedef QList<QPoint> QPointList;

class Shape
{
public:

    static Polygon* ClippingPolygon;

    //interface
    virtual QRect GetRect() = 0;
    virtual void Draw(QImage &img) = 0;
    virtual void Move(QPoint pos) = 0;
    virtual void ClipToPolygon(QImage &img) = 0;

    //declaration
    void Move(int x, int y)         { Move(QPoint(x, y)); }
    QColor GetColor()               { return lineColor; }
    void SetColor(QColor color)     { this->lineColor = color; }
    void SetTexture(QImage image)   { this->texture = image; }
    void SetType(Globals::ShapeType newType) { type = newType; }
    Globals::ShapeType GetType()    { return type; }
    friend QDebug operator<< (QDebug d, const Shape *model);
    bool isFilled;
protected:
    QColor lineColor;
    QImage texture = QImage(1, 1, QImage::Format_Mono);
    Globals::ShapeType type;
};

inline QDebug operator<< (QDebug d, Shape* s) {
    d << s->GetType() << s->GetColor() << s->GetRect();
    return d;
}

#endif // SHAPE_H
