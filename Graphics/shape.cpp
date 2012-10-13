#include "shape.h"

Shape::Shape()
{
    rect = QRect(0, 0, 0, 0);
}

Shape::Shape(QColor color)
{
    Shape();
    this->color = color;
}

Shape::Shape(QPointList points, QColor color)
{
    Shape();
    SetColor(color);
    SetPoints(points);
}

void Shape::SetColor(QColor color)
{
    this->color = color;
}

void Shape::SetPoints(QPointList points)
{
    this->pointList = points;
    setRect();
}

QPointList Shape::GetPoints()
{
    return pointList;
}

QColor Shape::GetColor()
{
    return color;
}

QRect Shape::GetRect()
{
    return rect;
}

void Shape::setRect()
{
    rect = QRect(pointList.first(), pointList.last());
    foreach (QPoint p, pointList)
    {
        if (p.x() > rect.right())
            rect.setRight(p.x());
        if (p.x() < rect.left())
            rect.setLeft(p.x());
        if (p.y() > rect.bottom())
            rect.setBottom(p.y());
        if (p.y() < rect.top())
            rect.setTop(p.y());
    }
}
