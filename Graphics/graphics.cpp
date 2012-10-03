#include "graphics.h"

Graphics::Graphics()
{
}

QPointList Graphics::DrawLine(const int x1, const int y1, const int x2, const int y2)
{
    QPointList pointList;

    //Z wikipedi    http://pl.wikipedia.org/wiki/Algorytm_Bresenhama
    // zmienne pomocnicze
    int d, dx, dy, ai, bi, xi, yi;
    int x = x1, y = y1;
    // ustalenie kierunku rysowania
    if (x1 < x2)
    {
        xi = 1;
        dx = x2 - x1;
    }
    else
    {
        xi = -1;
        dx = x1 - x2;
    }
    // ustalenie kierunku rysowania
    if (y1 < y2)
    {
        yi = 1;
        dy = y2 - y1;
    }
    else
    {
        yi = -1;
        dy = y1 - y2;
    }
    pointList.reserve(dx + dy);
    // pierwszy piksel
    pointList.append(QPoint(x, y));
    // oś wiodąca OX
    if (dx > dy)
    {
        ai = (dy - dx) * 2;
        bi = dy * 2;
        d = bi - dx;
        // pętla po kolejnych x
        while (x != x2)
        {
            // test współczynnika
            if (d >= 0)
            {
                x += xi;
                y += yi;
                d += ai;
            }
            else
            {
                d += bi;
                x += xi;
            }
            pointList.append(QPoint(x, y));
        }
    }
    // oś wiodąca OY
    else
    {
        ai = ( dx - dy ) * 2;
        bi = dx * 2;
        d = bi - dy;
        // pętla po kolejnych y
        while (y != y2)
        {
            // test współczynnika
            if (d >= 0)
            {
                x += xi;
                y += yi;
                d += ai;
            }
            else
            {
                d += bi;
                y += yi;
            }
            pointList.append(QPoint(x, y));
        }
    }
    return pointList;
}

QPointList Graphics::DrawLine( const QPoint begin, const QPoint end)
{
    return DrawLine(begin.x(), begin.y(), begin.y(), end.y());
}
