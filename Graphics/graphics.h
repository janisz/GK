#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QPoint>
#include <QColor>
#include <QList>
#include <QDebug>
#include <QImage>
#include "shape.h"
#include "line.h"
#include <cmath>

typedef QList<QPoint> QPointList;

class Graphics
{
public:
    Graphics();
    void SetCanvas(QImage canvas);
    QImage GetCanvas();

    void SetPixel(const QPoint point, const QColor color, QImage& image, const int alpha);
    void SetPixel(const int x, const int y, const QColor color, QImage& image, const int alpha);
    void SetPixel(const QPoint point, const QColor color, const int alpha);
    void SetPixel(const int x, const int y, const QColor color, const int alpha);
    void AddShape(Shape* s);
    void SetShapes(QList<Shape*> s);
    QList<Shape*> GetShapes();
    void DeleteLastShape();

    void Repaint();

    Shape* GetShapeAt(QPoint point);

    QImage DrawGrid(const int);
    QImage DrawShape(Shape*);
    void DrawShape(Shape*, QImage&);
    bool isPointInRect(QPoint point, QRect rect);
private:
    QImage canvas;
    QImage newShape;
    static QColor defaultColor;
    QList<Shape*> shapeList;

protected:
    QPointList plot8points(int cx, int cy, int x, int y)
    {
      QPointList p = plot4points(cx, cy, x, y);
      if (x != y) p.append(plot4points(cx, cy, y, x));
      return p;
    }

    QPointList plot4points(int cx, int cy, int x, int y)
    {
      QPointList points;
      points.append(QPoint(cx + x, cy + y));

      if (x != 0) points.append(QPoint(cx - x, cy + y));
      if (y != 0) points.append(QPoint(cx + x, cy - y));
      if (x != 0 && y != 0) points.append(QPoint(cx - x, cy - y));

      return points;
    }
};

#endif // GRAPHICS_H
