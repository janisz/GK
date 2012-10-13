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
        for (int j=0;j<canvas.height();j++)
        {
            SetPixel(i, j, Qt::gray);
        }
    }

    for (int i=0;i<canvas.height();i+=gap)
    {
        for (int j=0;j<canvas.width();j++)
        {
            SetPixel(j, i, Qt::gray);
        }
    }
}

void Graphics::Circle(const int x0, const int y0, const int radius, QColor color)
{
    int error = -radius;
    int x = radius;
    int y = 0;

    // The following while loop may be altered to 'while (x > y)' for a
    // performance benefit, as long as a call to 'plot4points' follows
    // the body of the loop. This allows for the elimination of the
    // '(x != y)' test in 'plot8points', providing a further benefit.
    //
    // For the sake of clarity, this is not shown here.
    while (x >= y)
    {
      plot8points(x0, y0, x, y, color);

      error += y;
      ++y;
      error += y;

      // The following test may be implemented in assembly language in
      // most machines by testing the carry flag after adding 'y' to
      // the value of 'error' in the previous step, since 'error'
      // nominally has a negative value.
      if (error >= 0)
      {
        error -= x;
        --x;
        error -= x;
      }
    }
}

void Graphics::Circle(const QPoint centre, const int radius, QColor color)
{
    Circle(centre.x(), centre.y(), radius, color);
}

void Graphics::AddShape(Shape s)
{
    shapeList.append(s);
}

void Graphics::SetShapes(QList<Shape> s)
{
    shapeList = s;
}

void Graphics::Repaint()
{
    foreach (Shape s, shapeList)
    {
        QColor c = s.GetColor();
        foreach (QPoint p, s.GetPoints())
        {
            SetPixel(p, c);
        }
    }
}
