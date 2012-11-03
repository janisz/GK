#include "polygon.h"

Polygon::Polygon()
{
    SetType(Globals::Polygon);
}

void Polygon::AddVertex(QPoint newVertex)
{
    vertexs.append(newVertex);
}

void Polygon::ChangeLastVertex(QPoint vertex)
{
    vertexs.back() = vertex;
}

void Polygon::Move(QPoint pos)
{
    for (int i=0;i<vertexs.size();i++)
    {
        vertexs[i] += pos;
    }
}

void Polygon::Draw(QImage &img)
{
    for (int i=1;i<vertexs.size();i++)
    {
        Line l(vertexs[i-1], vertexs[i], color);
        l.Draw(img);
    }
    Line l(vertexs.first(), vertexs.back(), color);
    l.Draw(img);
}

QRect Polygon::GetRect()
{
    QPoint leftTop = vertexs.first(), rightDown = vertexs.back();
    foreach (QPoint p, vertexs)
    {
        leftTop.setX(leftTop.x() < p.x() ? leftTop.x(): p.x());
        leftTop.setY(leftTop.y() < p.y() ? leftTop.y(): p.y());

        rightDown.setX(rightDown.x() > p.x() ? rightDown.x(): p.x());
        rightDown.setX(rightDown.y() > p.y() ? rightDown.y(): p.y());
    }

    return QRect(leftTop, rightDown);

}
