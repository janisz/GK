#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include "graphics.h"
#include <QPoint>
#include <QRect>
#include "polygon.h"

class Line : public Shape
{
public:
    Line(QPoint begin, QPoint end, QColor lineColor);
    void SetColor(QColor lineColor);
    void Draw(QImage &img);
    void Move(QPoint pos);
    QRect GetRect();
protected:
    bool ClipToRect(int &x0, int &y0, int &x1, int &y1);
    bool ClipToPolygon(int &x0, int &y0, int &x1, int &y1);
    void ClipToPolygon(QImage &img) {};
    QPoint begin;
    QPoint end;
};

#endif // LINE_H
