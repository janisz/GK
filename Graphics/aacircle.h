#ifndef AACIRCLE_H
#define AACIRCLE_H

#include "circle.h"
#include <cmath>

class AACircle : public Circle
{
public:
    AACircle();
    AACircle(QPoint pos, int r, QColor c) : Circle(pos, r, c) { qDebug() << "Create AACircle"; }
    void Draw(QImage &img);
};

#endif // AACIRCLE_H
