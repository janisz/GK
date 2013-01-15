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

//Shape Graphics::Circle(const int x0, const int y0, const int radius, QColor color, int size)
//{
////    QPointList points;

////    int error = -radius;
////    int x = radius;
////    int y = 0;

////    // The following while loop may be altered to 'while (x > y)' for a
////    // performance benefit, as long as a call to 'plot4points' follows
////    // the body of the loop. This allows for the elimination of the
////    // '(x != y)' test in 'plot8points', providing a further benefit.
////    //
////    // For the sake of clarity, this is not shown here.
////    while (x >= y)
////    {
////        for (int i=0;i<size;i++)
////        {
////            for (int j=0;j<size;j++)
////            {
////                points.append(plot8points(x0+i, y0+j, x, y));
////            }
////        }

////      error += y;
////      ++y;
////      error += y;

////      // The following test may be implemented in assembly language in
////      // most machines by testing the carry flag after adding 'y' to
////      // the value of 'error' in the previous step, since 'error'
////      // nominally has a negative value.
////      if (error >= 0)
////      {
////        error -= x;
////        --x;
////        error -= x;
////      }
////    }

////    return Shape(points, color);
//}

//Shape Graphics::Circle(const QPoint centre, const int radius, QColor color, int size)
//{
//    return Circle(centre.x(), centre.y(), radius, color, size);
//}


//Shape Graphics::Circle(const int x0, const int y0, const int radius, QColor color)
//{
////    QPointList points;

////    int error = -radius;
////    int x = radius;
////    int y = 0;

////    // The following while loop may be altered to 'while (x > y)' for a
////    // performance benefit, as long as a call to 'plot4points' follows
////    // the body of the loop. This allows for the elimination of the
////    // '(x != y)' test in 'plot8points', providing a further benefit.
////    //
////    // For the sake of clarity, this is not shown here.
////    while (x >= y)
////    {
////      points.append(plot8points(x0, y0, x, y));

////      error += y;
////      ++y;
////      error += y;

////      // The following test may be implemented in assembly language in
////      // most machines by testing the carry flag after adding 'y' to
////      // the value of 'error' in the previous step, since 'error'
////      // nominally has a negative value.
////      if (error >= 0)
////      {
////        error -= x;
////        --x;
////        error -= x;
////      }
////    }

////    return Shape(points, color);
//}

//Shape Graphics::Circle(const QPoint centre, const int radius, QColor color)
//{
//    return Circle(centre.x(), centre.y(), radius, color);
//}


//Shape Graphics::AACircle(const QPoint centre, const int radius, QColor color)
//{
//    return AACircle(centre.x(), centre.y(), radius, color);
//}

////Distance to ceil:
//inline double DC(int r, int y){
//  double x = sqrt(r*r-y*y);
//  return ceil(x) - x;
//}

//inline void SetPoint(int x, int y, int alpha, QPointList& p, QList<int>& a)
//{
////    p.append(QPoint(x, y));
////    a.append(alpha);
//}

//Shape Graphics::AACircle(const int x0, const int y0, const int radius, QColor color)
//{
////    int y=-1;
////    int x=radius;
////    float d=0;
////    int A =255;
////    QPointList points;
////    QList<int> alpha;


////    while( x>y ){
////         y++;

////         if( DC(radius,y) <= d ) x--;

////         int A1 = A * DC(radius,y);
////         int A2 = A * (1-DC(radius,y));

////         SetPoint(x + x0, y + y0, A, points, alpha);
////         SetPoint(x -1 + x0, y + y0, A1, points, alpha);
////         SetPoint(x +1 + x0, y + y0, A2, points, alpha);

////         SetPoint(y + x0, x + y0, A, points, alpha);
////         SetPoint(y + x0, x -1 + y0, A1, points, alpha);
////         SetPoint(y + x0, x +1 + y0, A2, points, alpha);

////         SetPoint(-x + x0, y + y0, A, points, alpha);
////         SetPoint(-x +1 + x0, y + y0, A1, points, alpha);
////         SetPoint(-x -1 + x0, y + y0, A2, points, alpha);

////         SetPoint(-y + x0, x + y0, A, points, alpha);
////         SetPoint(-y + x0, x -1 + y0, A1, points, alpha);
////         SetPoint(-y + x0, x +1 + y0, A2, points, alpha);

////         SetPoint(x + x0, -y + y0, A, points, alpha);
////         SetPoint(x -1 + x0, -y + y0, A1, points, alpha);
////         SetPoint(x +1 + x0, -y + y0, A2, points, alpha);

////         SetPoint(y + x0, -x + y0, A, points, alpha);
////         SetPoint(y + x0, -x +1 + y0, A1, points, alpha);
////         SetPoint(y + x0, -x -1 + y0, A2, points, alpha);

////         SetPoint(-y + x0, -x + y0, A, points, alpha);
////         SetPoint(-y + x0, -x +1 + y0, A1, points, alpha);
////         SetPoint(-y + x0, -x -1 + y0, A2, points, alpha);

////         SetPoint(-x + x0, -y + y0, A, points, alpha);
////         SetPoint(-x +1 + x0, -y + y0, A1, points, alpha);
////         SetPoint(-x -1 + x0, -y + y0, A2, points, alpha);

////         d = DC(radius,y);
////    }
////    return Shape(points, color, alpha);
//}

//Shape Graphics::Ellipse( int x0,  int y0,  int x1,  int y1, const QColor color)
//{

////    QPointList points;

////    int a = abs(x1-x0), b = abs(y1-y0), b1 = b&1; /* values of diameter */
////    long dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
////    long err = dx+dy+b1*a*a, e2; /* error of 1.step */

////    if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
////    if (y0 > y1) y0 = y1; /* .. exchange them */
////    y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
////    a *= 8*a; b1 = 8*b*b;

////    do {
////        points.append(QPoint(x1, y0)); /*   I. Quadrant */
////        points.append(QPoint(x0, y0)); /*  II. Quadrant */
////        points.append(QPoint(x0, y1)); /* III. Quadrant */
////        points.append(QPoint(x1, y1)); /*  IV. Quadrant */
////        e2 = 2*err;
////        if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */
////        if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
////    } while (x0 <= x1);

////    while (y0-y1 < b) {  /* too early stop of flat ellipses a=1 */
////        points.append(QPoint(x0-1, y0)); /* -> finish tip of ellipse */
////        points.append(QPoint(x1+1, y0++));
////        points.append(QPoint(x0-1, y1));
////        points.append(QPoint(x1+1, y1--));
////    }

////    return Shape(points, color);
//}

//Shape Graphics::Ellipse(const QPoint first, const QPoint second, const QColor color)
//{
//    return Ellipse(first.x(), first.y(), second.x(), second.y(), color);
//}

void Graphics::AddShape(Shape *s)
{
    shapeList.append(s);
}

void Graphics::DeleteLastShape()
{
    if (!shapeList.isEmpty())
    {
        shapeList.pop_back();
        qDebug() << "Remove shape: ";
    }
    else
        qDebug() << "Shape list is empty";
}

void Graphics::SetShapes(QList<Shape *> s)
{
    shapeList = s;
}

void Graphics::Repaint()
{
    canvas.fill(Qt::transparent);
    foreach (Shape* s, shapeList)
    {
        s->Draw(canvas);
    }
}

QImage Graphics::DrawShape(Shape *shape)
{
    newShape.fill(Qt::transparent);
    if (shape)
        shape->Draw(newShape);
    return newShape;
}

void Graphics::DrawShape(Shape *shape, QImage& image)
{
    shape->Draw(image);
}

QList<Shape *> Graphics::GetShapes()
{
    return shapeList;
}

Shape *Graphics::GetShapeAt(QPoint point)
{
    Shape* s;
    for (int i=0;i<shapeList.length(); i++)
    {
        s = shapeList[i];
        if (s->GetRect().contains(point))
        {
            shapeList.removeAt(i);
            return s;
        }
    }
    s = shapeList.front();
    shapeList.pop_front();
    return s;
}
