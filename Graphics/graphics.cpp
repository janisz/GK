#include "graphics.h"

Graphics::Graphics()
{
    newShape = QImage(800, 600, QImage::Format_ARGB32);
}

void Graphics::SetCanvas(QImage canvas)
{
    this->canvas = canvas;
}

QImage Graphics::GetCanvas()
{
    Repaint();
    return (this->canvas);
}

bool Graphics::isPointInRect(QPoint point, QRect rect)
{
    return (point.x() > rect.left() && point.x() < rect.right() &&
            point.y() > rect.top()  && point.y() < rect.bottom());
}

void Graphics::SetPixel(const QPoint point, const QColor color, const int alpha = 255)
{
//    qDebug() << point << color;
    if (isPointInRect(point, canvas.rect()))
        canvas.setPixel(point, qRgba(color.red(), color.green(), color.blue(), alpha));

}

void Graphics::SetPixel(const int x, const int y, const QColor color, const int alpha = 255)
{
    SetPixel(QPoint(x, y), color, alpha);
}

void Graphics::SetPixel(const QPoint point, const QColor color, QImage& image, const int alpha = 255)
{
    if (isPointInRect(point, image.rect()))
        image.setPixel(point, qRgba(color.red(), color.green(), color.blue(), alpha));

}

void Graphics::SetPixel(const int x, const int y, const QColor color, QImage& image, const int alpha = 255)
{
    SetPixel(QPoint(x, y), color, image, alpha);
}


Shape Graphics::DrawLine(int x0, int y0, const int x1, const int y1, const QColor color)
{
    QPointList points;

    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx-dy;

    while (true)
    {
        points.append(QPoint(x0,y0));

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

    return Shape(points, color);
}

Shape Graphics::DrawLine( const QPoint begin, const QPoint end, const QColor color)
{
    return DrawLine(begin.x(), begin.y(), end.x(), end.y(), color);
}

Shape Graphics::DrawAALine(const QPoint begin, const QPoint end, const QColor color)
{
    return DrawAALine(begin.x(), begin.y(), end.x(), end.y(), color);
}

Shape Graphics::DrawAALine(int x1, int y0, const int x2, const int y2, const QColor color)
{

}


QImage Graphics::DrawGrid(const int gap)
{
    QImage grid(800, 600, QImage::Format_ARGB32);
    grid.fill(Qt::black);

    for (int i=0;i<canvas.width(); i+=gap)
    {
        for (int j=0;j<canvas.height();j++)
        {
            grid.setPixel(i, j, Qt::gray);
        }
    }

    for (int i=0;i<canvas.height();i+=gap)
    {
        for (int j=0;j<canvas.width();j++)
        {
            grid.setPixel(j, i, Qt::gray);
        }
    }

    return grid;
}

Shape Graphics::Circle(const int x0, const int y0, const int radius, QColor color)
{
    QPointList points;

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
      points.append(plot8points(x0, y0, x, y));

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

    return Shape(points, color);
}

Shape Graphics::Circle(const QPoint centre, const int radius, QColor color)
{
    return Circle(centre.x(), centre.y(), radius, color);
}


Shape Graphics::AACircle(const QPoint centre, const int radius, QColor color)
{
    return AACircle(centre.x(), centre.y(), radius, color);
}

//Distance to ceil:
inline double DC(int r, int y){
  double x = sqrt(r*r-y*y);
  return ceil(x) - x;
}

inline void SetPoint(int x, int y, int alpha, QPointList& p, QList<int>& a)
{
    p.append(QPoint(x, y));
    a.append(alpha);
}

Shape Graphics::AACircle(const int x0, const int y0, const int radius, QColor color)
{
    int y=-1;
    int x=radius;
    float d=0;
    int A =255;
    QPointList points;
    QList<int> alpha;


    while( x>y ){
         y++;

         if( DC(radius,y) <= d ) x--;

         int A1 = A * DC(radius,y);
         int A2 = A * (1-DC(radius,y));

         SetPoint(x + x0, y + y0, A, points, alpha);
         SetPoint(x -1 + x0, y + y0, A1, points, alpha);
         SetPoint(x +1 + x0, y + y0, A2, points, alpha);

         SetPoint(y + x0, x + y0, A, points, alpha);
         SetPoint(y + x0, x -1 + y0, A1, points, alpha);
         SetPoint(y + x0, x +1 + y0, A2, points, alpha);

         SetPoint(-x + x0, y + y0, A, points, alpha);
         SetPoint(-x +1 + x0, y + y0, A1, points, alpha);
         SetPoint(-x -1 + x0, y + y0, A2, points, alpha);

         SetPoint(-y + x0, x + y0, A, points, alpha);
         SetPoint(-y + x0, x -1 + y0, A1, points, alpha);
         SetPoint(-y + x0, x +1 + y0, A2, points, alpha);

         SetPoint(x + x0, -y + y0, A, points, alpha);
         SetPoint(x -1 + x0, -y + y0, A1, points, alpha);
         SetPoint(x +1 + x0, -y + y0, A2, points, alpha);

         SetPoint(y + x0, -x + y0, A, points, alpha);
         SetPoint(y + x0, -x +1 + y0, A1, points, alpha);
         SetPoint(y + x0, -x -1 + y0, A2, points, alpha);

         SetPoint(-y + x0, -x + y0, A, points, alpha);
         SetPoint(-y + x0, -x +1 + y0, A1, points, alpha);
         SetPoint(-y + x0, -x -1 + y0, A2, points, alpha);

         SetPoint(-x + x0, -y + y0, A, points, alpha);
         SetPoint(-x +1 + x0, -y + y0, A1, points, alpha);
         SetPoint(-x -1 + x0, -y + y0, A2, points, alpha);

         d = DC(radius,y);
    }
    return Shape(points, color, alpha);
}

void Graphics::AddShape(Shape s)
{
    shapeList.append(s);
}

void Graphics::DeleteLastShape()
{
    if (!shapeList.isEmpty())
        shapeList.pop_back();
}

void Graphics::SetShapes(QList<Shape> s)
{
    shapeList = s;
}

void Graphics::Repaint()
{
    canvas.fill(Qt::transparent);
    foreach (Shape s, shapeList)
    {
        QColor c = s.GetColor();
        //foreach (QPoint p, s.GetPoints())
        for (int i=0;i<s.GetPoints().size();i++)
        {
            QPoint p = s.GetPoints()[i];
            int a = s.GetAlpha().isEmpty() ? 255 : s.GetAlpha()[i];
            SetPixel(p, c, a);
        }
    }
}

QImage Graphics::DrawShape(Shape shape)
{
    newShape.fill(Qt::transparent);
    for (int i=0;i<shape.GetPoints().size();i++)
    {
        QPoint p = shape.GetPoints()[i];
        int a = shape.GetAlpha().isEmpty() ? 255 : shape.GetAlpha()[i];
        SetPixel(p, shape.GetColor(), newShape, a);
    }

    return newShape;

}

void Graphics::DrawShape(Shape shape, QImage& image)
{
    //foreach (QPoint p, shape.GetPoints())
    for (int i=0;i<shape.GetPoints().size();i++)
    {
        QPoint p = shape.GetPoints()[i];
        int a = shape.GetAlpha().isEmpty() ? 255 : shape.GetAlpha()[i];
        SetPixel(p, shape.GetColor(), image, a);
    }

}

QList<Shape> Graphics::GetShapes()
{
    return shapeList;
}

Shape Graphics::GetShapeAt(QPoint point)
{
    Shape s;
    for (int i=0;i<shapeList.length(); i++)
    {
        s = shapeList[i];
        if (isPointInRect(point, s.GetRect()))
        {
            shapeList.removeAt(i);
            return s;
        }
    }
    s = shapeList.front();
    shapeList.pop_front();
    return s;
}
