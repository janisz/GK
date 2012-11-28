#include "line.h"

Line::Line(QPoint begin, QPoint end, QColor color)
{
    this->begin = begin;
    this->end = end;
    this->lineColor = color;
    this->type = Globals::Line;
}

void Line::Move(QPoint pos)
{
    begin += pos;
    end += pos;
}

QRect Line::GetRect()
{
    return QRect(begin, end);
}

const int INSIDE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;
int xmax = 800-1;
int xmin = 0;
int ymax = 600-1;
int ymin = 0;
int inline Code(int x, int y)
{
    int code;

    code = INSIDE;          // initialised as being inside of clip window

    if (x < xmin)           // to the left of clip window
            code |= LEFT;
    else if (x > xmax)      // to the right of clip window
            code |= RIGHT;
    if (y < ymin)           // below the clip window
            code |= BOTTOM;
    else if (y > ymax)      // above the clip window
            code |= TOP;

    return code;
}

// Cohen–Sutherland clipping algorithm clips a line.
// Source: http://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
bool Line::ClipToRect(int &x0, int &y0, int &x1, int &y1)
{
    int outcode0 = Code(x0, y0);
    int outcode1 = Code(x1, y1);
    bool accept = false;

    while (true)
    {
            if (!(outcode0 | outcode1))
            {
                    accept = true;
                    break;
            }
            else if (outcode0 & outcode1)   break;
            else {
                    int x, y;

                    // At least one endpoint is outside the clip rectangle; pick it.
                    int outcodeOut = outcode0? outcode0 : outcode1;

                    //y= y0 + a * (x - x0), x = x0 + (1 / a) * (y - y0)
                    if (outcodeOut & TOP) { //up
                            x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                            y = ymax;
                    }
                    else if (outcodeOut & BOTTOM) { // down
                            x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                            y = ymin;
                    }
                    else if (outcodeOut & RIGHT) {  // right
                            y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                            x = xmax;
                    }
                    else {   // left
                            y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                            x = xmin;
                    }

                    if (outcodeOut == outcode0) {
                            x0 = x; y0 = y;
                            outcode0 = Code(x0, y0);
                    }
                    else {
                            x1 = x; y1 = y;
                            outcode1 = Code(x1, y1);
                    }
            }
    }

    return accept;
}

long long int inline CrossProductLength(int ax, int ay, int bx, int by, int cx, int cy)
{
    int Ax = ax - bx, Ay = ay - by;
    int Bx = cx - bx, By = cy - by;
    return (Ax * By) - (Ay * Bx);
}

bool Inside(QPoint p, Edge e)
{
    return CrossProductLength(p.x(), p.y(), e.first.x(), e.first.y(), e.second.x(), e.second.y()) >= 0;
}

QPoint ComputeIntersection(QPoint A, QPoint B, Edge E)
{
    int x1 = A.x();
    int y1 = A.y();
    int x2 = B.x();
    int y2 = B.y();

    int x3 = E.first.x();
    int y3 = E.first.y();
    int x4 = E.second.x();
    int y4 = E.second.y();

    int x12 = x1 - x2;
    int x34 = x3 - x4;
    int y12 = y1 - y2;
    int y34 = y3 - y4;

    float c = x12 * y34 - y12 * x34;

    int a = x1 * y2 - y1 * x2;
    int b = x3 * y4 - y3 * x4;

    int x = (a * x34 - b * x12) / c;
    int y = (a * y34 - b * y12) / c;

    return QPoint(x, y);
}

bool Line::ClipToPolygon(int &x0, int &y0, int &x1, int &y1)
{
    if (!ClippingPolygon) return true;
    QPoint S = QPoint(x0, y0);
    QPoint E = QPoint(x1, y1);
    foreach (Edge clipEdge, ClippingPolygon->Edges())
    {
            if (Inside(E, clipEdge))
            {
                if (!Inside(S, clipEdge))
                    S = ComputeIntersection(S, E, clipEdge);
            }
            else if (Inside(S, clipEdge))
                E = ComputeIntersection(S, E, clipEdge);
            else
                return false;
    }

    x0 = S.x(); y0 = S.y();
    x1 = E.x(); y1 = E.y();
    return true;
}

void Line::Draw(QImage &img)
{
    int x0 = begin.x();
    int y0 = begin.y();

    int x1 = end.x();
    int y1 = end.y();

    if (!ClipToPolygon(x0, y0, x1, y1)) return;
    if (!ClipToRect(x0, y0, x1, y1)) return;

    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx-dy;

    while (true)
    {
        img.setPixel(x0,y0, qRgb(lineColor.red(), lineColor.green(), lineColor.blue()));

        if ((x0 == x1) && (y0 == y1))
                break;

        int e2 = 2*err;

        if (e2 > -dy)
        {
            err = err - dy;
            x0 = x0 + sx;
        }
        if (e2 <  dx)
        {
            err = err + dx;
            y0 = y0 + sy;
        }
    }
}
