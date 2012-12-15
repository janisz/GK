#include "circle.h"

void plot4points(int cx, int cy, int x, int y, QColor color, QImage &img)
{
  img.setPixel(cx + x, cy + y, color.rgb());
  if (x != 0)  img.setPixel(cx - x, cy + y, color.rgb());
  if (y != 0) img.setPixel(cx + x, cy - y, color.rgb());
  if (x != 0 && y != 0) img.setPixel(cx - x, cy - y, color.rgb());
}

void plot8points(int cx, int cy, int x, int y, QColor color, QImage &img)
{
  plot4points(cx, cy, x, y, color, img);
  if (x != y) plot4points(cx, cy, y, x, color, img);
}

void Circle::Draw(QImage &img)
{
    int error = -Radius;
    int x = Radius;
    int y = 0;

    // The following while loop may be altered to 'while (x > y)' for a
    // performance benefit, as long as a call to 'plot4points' follows
    // the body of the loop. This allows for the elimination of the
    // '(x != y)' test in 'plot8points', providing a further benefit.
    //
    // For the sake of clarity, this is not shown here.
    while (x >= y)
    {
      plot8points(Centre.x(), Centre.y(), x, y, lineColor ,img);

      error += y;
      ++y;
      error += y;

      // The following test may be implemented in assembly language in
      // most machines by testing the carry flag after adding 'y' to
      // the value of 'error' in the previous step, since 'error'
      // nominally has a negative value.
      if (error >= 0)
      {
        error -= x;
        --x;
        error -= x;
      }
    }
}
