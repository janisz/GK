#include "line.h"

Line::Line(QPoint begin, QPoint end, QColor color)
{
    this->begin = begin;
    this->end = end;
    this->color = color;
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
                    if (outcodeOut & BOTTOM) { // down
                            x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                            y = ymin;
                    }
                    if (outcodeOut & RIGHT) {  // right
                            y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                            x = xmax;
                    }
                    if (outcodeOut & LEFT) {   // left
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

void Line::Draw(QImage &img)
{
    int x0 = begin.x();
    int y0 = begin.y();

    int x1 = end.x();
    int y1 = end.y();

    if (!ClipToRect(x0, y0, x1, y1)) return;

    int dx = abs(x1-x0);
    int dy = abs(y1-y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx-dy;

    while (true)
    {
        img.setPixel(x0,y0, qRgb(color.red(), color.green(), color.blue()));

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
