#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QPoint>
#include <QList>

typedef QList<QPoint> QPointList;

class Graphics
{
public:
    Graphics();
    static QPointList DrawLine(int x1, int y1, int x2, int y2);
    static QPointList DrawLine( const QPoint begin, const QPoint end);
};

#endif // GRAPHICS_H
