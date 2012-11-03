#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include "graphics.h"
#include <QPoint>
#include <QRect>

class Line : public Shape
{
public:
    Line();
    Line(QPoint begin, QPoint end, QColor color);
    void SetColor(QColor color);
    void Draw(QImage &img);
    void Move(QPoint pos);
    QRect GetRect();
protected:
    QPoint begin;
    QPoint end;
    QColor color;
};

#endif // LINE_H
