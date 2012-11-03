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


long long int inline CrossProductLength(int ax, int ay, int bx, int by, int cx, int cy)
{
    int Ax = ax - bx, Ay = ay - by;
    int Bx = cx - bx, By = cy - by;
    return (Ax * By) - (Ay * Bx);
}


bool Polygon::isConvex()
{
    // For each set of three adjacent points A, B, C,
    // find the dot product AB · BC. If the sign of
    // all the dot products is the same, the angles
    // are all positive or negative (depending on the
    // order in which we visit them) so the polygon
    // is convex.
    bool got_negative = false;
    bool got_positive = false;
    int num_points = vertexs.size();
    int B, C;
    for (int A = 0; A < num_points; A++)
    {
        B = (A + 1) % num_points;
        C = (B + 1) % num_points;

        long long int cross_product =
            CrossProductLength(
                    vertexs[A].x(), vertexs[A].y(),
                    vertexs[B].x(), vertexs[B].y(),
                    vertexs[C].x(), vertexs[C].y());
        if (cross_product < 0)
        {
            got_negative = true;
        }
        else if (cross_product > 0)
        {
            got_positive = true;
        }
        if (got_negative && got_positive) return false;
    }

    // If we got this far, the polygon is convex.
    return true;
}
