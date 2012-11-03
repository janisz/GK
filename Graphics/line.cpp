#include "line.h"

Line::Line()
{
    begin = end = QPoint(0, 0);
    color = Qt::red;
    SetType(Globals::Line);
}

Line::Line(QPoint begin, QPoint end, QColor color)
{
    this->begin = begin;
    this->end = end;
    this->color = color;
}

void Line::Move(QPoint pos)
{
    begin += pos;
    end += pos;
}

QRect Line::GetRect()
{
    return QRect(begin, end);
}

void Line::Draw(QImage &img)
{
    int x0 = begin.x();
    int y0 = begin.y();

    int x1 = end.x();
    int y1 = end.y();

    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx-dy;

    while (true)
    {
        img.setPixel(x0,y0, qRgb(color.red(), color.green(), color.blue()));

        if ((x0 == x1) && (y0 == y1))
                break;

        int e2 = 2*err;

        if (e2 > -dy)
        {
            err = err - dy;
            x0 = x0 + sx;
        }
        if (e2 <  dx)
        {
            err = err + dx;
            y0 = y0 + sy;
        }
    }
}
