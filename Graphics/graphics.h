#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QPoint>
#include <QColor>
#include <QList>
#include <QDebug>
#include <QImage>

typedef QList<QPoint> QPointList;

class Graphics
{
public:
    Graphics();
    void SetCanvas(QImage canvas);
    QImage GetCanvas();
    void DrawLine(int x1, int y0, const int x2, const int y2, const QColor color);
    void DrawLine(const QPoint begin, const QPoint end, const QColor color);
    void Circle(const QPoint centre, const int radius, QColor color);
    void Circle(const int x0, const int y0, const int radius, QColor color);
    void SetPixel(const QPoint point, const QColor color);
    void SetPixel(const int x, const int y, const QColor color);

    //helpers
    void DrawGrid(const int);
    bool isPointInRect(QPoint point, QRect rect);
private:
    QImage canvas;
    static QColor defaultColor;

protected:
    void plot8points(int cx, int cy, int x, int y, QColor color)
    {
      plot4points(cx, cy, x, y, color);
      if (x != y) plot4points(cx, cy, y, x, color);
    }
    void plot4points(int cx, int cy, int x, int y, QColor color)
    {
      SetPixel(cx + x, cy + y, color);
      if (x != 0) SetPixel(cx - x, cy + y, color);
      if (y != 0) SetPixel(cx + x, cy - y, color);
      if (x != 0 && y != 0) SetPixel(cx - x, cy - y, color);
    }
};

#endif // GRAPHICS_H
