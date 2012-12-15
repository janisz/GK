#include "aacircle.h"

//Distance to ceil:
inline double DC(int r, int y){
  double x = std::sqrt(r*r-y*y);
  return std::ceil(x) - x;
}

void AACircle::Draw(QImage &img)
{

    int x0 = Centre.x();
    int y0 = Centre.y();
    int y=-1;
    int x=Radius;
    float d=0;
    QRgb A = lineColor.rgb();
    QPointList points;
    QList<int> alpha;


    while( x>y ){
         y++;

         if( DC(Radius,y) <= d ) x--;

         QRgb A1 = QColor(lineColor.red() * DC(Radius,y), lineColor.blue() * DC(Radius,y), lineColor.green() * DC(Radius,y)).rgb();
         QRgb A2 = QColor(lineColor.red() * (1-DC(Radius,y)), lineColor.blue() * (1-DC(Radius,y)), lineColor.green() * (1-DC(Radius,y))).rgb();

         img.setPixel(x + x0, y + y0, A);
         img.setPixel(x -1 + x0, y + y0, A1);
         img.setPixel(x +1 + x0, y + y0, A2);

         img.setPixel(y + x0, x + y0, A);
         img.setPixel(y + x0, x -1 + y0, A1);
         img.setPixel(y + x0, x +1 + y0, A2);

         img.setPixel(-x + x0, y + y0, A);
         img.setPixel(-x +1 + x0, y + y0, A1);
         img.setPixel(-x -1 + x0, y + y0, A2);

         img.setPixel(-y + x0, x + y0, A);
         img.setPixel(-y + x0, x -1 + y0, A1);
         img.setPixel(-y + x0, x +1 + y0, A2);

         img.setPixel(x + x0, -y + y0, A);
         img.setPixel(x -1 + x0, -y + y0, A1);
         img.setPixel(x +1 + x0, -y + y0, A2);

         img.setPixel(y + x0, -x + y0, A);
         img.setPixel(y + x0, -x +1 + y0, A1);
         img.setPixel(y + x0, -x -1 + y0, A2);

         img.setPixel(-y + x0, -x + y0, A);
         img.setPixel(-y + x0, -x +1 + y0, A1);
         img.setPixel(-y + x0, -x -1 + y0, A2);

         img.setPixel(-x + x0, -y + y0, A);
         img.setPixel(-x +1 + x0, -y + y0, A1);
         img.setPixel(-x -1 + x0, -y + y0, A2);

         d = DC(Radius,y);
    }
}
