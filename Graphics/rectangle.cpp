#include "rectangle.h"

Rectangle::Rectangle(QRect r)
{
    rect = r;
}

void Rectangle::Move(QPoint pos)
{
    rect.translate(pos);
    rect.setLeft(rect.left() > 0 ? rect.left() : 0);
    rect.setRight(rect.right() > 0 ? rect.right() : 0);
    rect.setBottom(rect.bottom() > 0 ? rect.bottom() : 0);
    rect.setTop(rect.top() > 0 ? rect.top() : 0);
}

void Rectangle::Draw(QImage &img)
{
    Line *l = new Line(rect.topLeft(), rect.topRight(), lineColor);
    l->Draw(img);
    delete l;
    l = new Line(rect.topLeft(), rect.bottomLeft(), lineColor);
    l->Draw(img);
    delete l;
    l = new Line(rect.topRight(), rect.bottomRight(), lineColor);
    l->Draw(img);
    delete l;
    l = new Line(rect.bottomLeft(), rect.bottomRight(), lineColor);
    l->Draw(img);
    delete l;
}
