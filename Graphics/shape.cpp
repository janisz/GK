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

Shape::Shape(QPointList points, QColor color, QList<int> alpha)
{
    Shape();
    SetColor(color);
    SetPoints(points, alpha);
}

void Shape::SetColor(QColor color)
{
    this->color = color;
}

void Shape::SetPoints( const QPointList points, QList<int> alpha)
{
    this->pointList = points;
    this->pointAplha = alpha;
    if (alpha.isEmpty())
    {
        pointAplha.reserve(points.size());
        qFill(pointAplha.begin(), pointAplha.end(), 0);
    }
    setRect();
}

QPointList Shape::GetPoints()
{
    return pointList;
}

QList<int> Shape::GetAlpha()
{
    return pointAplha;
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
