#include "graphics.h"

Graphics::Graphics()
{
}

void Graphics::SetCanvas(QImage canvas)
{
    this->canvas = canvas;
}

QImage Graphics::GetCanvas()
{
    canvas.save("/tmp/test.png", "PNG");
    return (this->canvas);
}

bool Graphics::isPointInRect(QPoint point, QRect rect)
{
    return (point.x() > rect.left() && point.x() < rect.right() &&
            point.y() > rect.top()  && point.y() < rect.bottom());
}

void Graphics::SetPixel(const QPoint point, const QColor color)
{
//    qDebug() << point << color;
    if (isPointInRect(point, canvas.rect()))
        canvas.setPixel(point, qRgb(color.red(), color.green(), color.blue()));

}

void Graphics::SetPixel(const int x, const int y, const QColor color)
{
    SetPixel(QPoint(x, y), color);
}


void Graphics::DrawLine(int x0, int y0, const int x1, const int y1, const QColor color)
{
    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx-dy;

    while (true)
    {
        SetPixel(x0,y0, color);

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

void Graphics::DrawLine( const QPoint begin, const QPoint end, const QColor color)
{
    return DrawLine(begin.x(), begin.y(), end.x(), end.y(), color);
}

void Graphics::DrawGrid(const int gap)
{
    for (int i=0;i<canvas.width(); i+=gap)
    {
        DrawLine(i, 0, i, canvas.height()-1, Qt::gray);
    }

    for (int i=0;i<canvas.height();i+=gap)
    {
        DrawLine(0, i, canvas.width()-1, i, Qt::gray);
    }
}
