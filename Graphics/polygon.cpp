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
    if (isFilled)   Fill(img);
    foreach (Edge e, Edges())
    {
        Line l(e.first, e.second, lineColor);
        l.Draw(img);
    }
}

QList<Edge> Polygon::Edges()
{
    QList<Edge> edges;
    for (int i=1;i<vertexs.size();i++)
    {
        edges.append(Edge(vertexs[i-1], vertexs[i]));
    }
    edges.append(Edge(vertexs.first(), vertexs.back()));
    return edges;
}

void Polygon::ClipToPolygon(QImage &img)
{
//    QList<QPoint> outputList;
//    outputList.append(this->vertexs);

//    for (int i=1;i<)
}

void Polygon::DrawTexturedHLine(int x0, int x1, int y, int h, int j, QImage &img)
{
    if (y <= 0 || y >= 600) return;
    x0 = x0 < 0 ? 1 : x0; x0 = x0 > 799 ? 799 : x0;
    x1 = x1 < 0 ? 1 : x1; x1 = x1 > 799 ? 799 : x1;
    j = j < 0 ? 0 : j;
    for (int i=x0; i<x1; i++)
    {
        img.setPixel(QPoint(i, y), texture.pixel((i-h)%texture.width(), j%texture.height()));
    }
}


bool CompEdges(const Edge a, const Edge b)
{
    return a.second.y() < b.second.y();
}

void Polygon::Fill(QImage &img)
{
    if (vertexs.count() < 3) return;

    QList<Edge> edgeList;
    QList<Edge> activeEdgeList;
    Edge e;

    int Ymax = this->GetRect().bottom();
    int Ymin = this->GetRect().top();
    int Xmin = this->GetRect().left();

    for (int i=1;i<vertexs.count();i++)
    {
        e.first = vertexs[i-1];
        e.second = vertexs[i];
        if (e.first.y() > e.second.y())
            std::swap(e.first, e.second);

        if (e.first.y() != e.second.y())
            edgeList.append(e);
    }

    e.first = vertexs.first();
    e.second = vertexs.last();
    if (e.first.y() > e.second.y())
        std::swap(e.first, e.second);

    if (e.first.y() != e.second.y())
        edgeList.append(e);

    qSort(edgeList.begin(), edgeList.end(), CompEdges);

    for (int y = Ymin; y < Ymax; y++)
    {
        QVector<int> points;

        while (edgeList.first().second.y() <= y)
            edgeList.removeFirst();

        for (int i=0;i<edgeList.count();i++)
        {
            e = edgeList[i];

            if (e.first.y() > y) continue;

            int x0 = e.first.x();   int y0 = e.first.y();
            int x1 = e.second.x();     int y1 = e.second.y();

            int x = x0 + ((x1-x0)/(double)(y1-y0))*(double)(y-y0);
            points.append(x);
        }

        qSort(points);
        for (int i=0;i<points.count()-1;i+=2)
        {
            DrawTexturedHLine(points[i], points[i+1], y, Xmin, -Ymin+y, img);
        }
        points.clear();
    }
}

QRect Polygon::GetRect()
{
    QPoint leftTop = vertexs.first(), rightDown = vertexs.back();
    foreach (QPoint p, vertexs)
    {
        leftTop.setX(leftTop.x() < p.x() ? leftTop.x(): p.x());
        leftTop.setY(leftTop.y() < p.y() ? leftTop.y(): p.y());

        rightDown.setX(rightDown.x() > p.x() ? rightDown.x(): p.x());
        rightDown.setY(rightDown.y() > p.y() ? rightDown.y(): p.y());
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
