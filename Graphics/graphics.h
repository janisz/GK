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
    uint QColorToUInt(QColor color);
    void DrawLine(int x1, int y0, const int x2, const int y2, const QColor color);
    void DrawLine(const QPoint begin, const QPoint end, const QColor color);
    void SetPixel(const QPoint point, const QColor color);
    void SetPixel(const int x, const int y, const QColor color);
    bool isPointInRect(QPoint point, QRect rect);
private:
    QImage canvas;
    static QColor defaultColor;
};

#endif // GRAPHICS_H
