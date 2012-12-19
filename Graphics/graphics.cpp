#include "graphics.h"

Graphics::Graphics()
{
    newShape = QImage(800, 600, QImage::Format_ARGB32);
}

void Graphics::SetCanvas(QImage canvas)
{
    this->canvas = canvas;
}

QImage Graphics::GetCanvas()
{
    Repaint();
    return (this->canvas);
}

bool Graphics::isPointInRect(QPoint point, QRect rect)
{
    return (point.x() > rect.left() && point.x() < rect.right() &&
            point.y() > rect.top()  && point.y() < rect.bottom());
}

void Graphics::SetPixel(const QPoint point, const QColor color, const int alpha = 255)
{
    canvas.setPixel(point, qRgba(color.red(), color.green(), color.blue(), alpha));
}

void Graphics::SetPixel(const int x, const int y, const QColor color, const int alpha = 255)
{
    SetPixel(QPoint(x, y), color, alpha);
}

void Graphics::SetPixel(const QPoint point, const QColor color, QImage& image, const int alpha = 255)
{
    if (isPointInRect(point, image.rect()))
        image.setPixel(point, qRgba(color.red(), color.green(), color.blue(), alpha));

}

void Graphics::SetPixel(const int x, const int y, const QColor color, QImage& image, const int alpha = 255)
{
    SetPixel(QPoint(x, y), color, image, alpha);
}

QImage Graphics::DrawGrid(const int gap)
{
    QImage grid(800, 600, QImage::Format_ARGB32);
    grid.fill(Qt::black);

    for (int i=0;i<canvas.width(); i+=gap)
    {
        for (int j=0;j<canvas.height();j++)
        {
            grid.setPixel(i, j, Qt::gray);
        }
    }

    for (int i=0;i<canvas.height();i+=gap)
    {
        for (int j=0;j<canvas.width();j++)
        {
            grid.setPixel(j, i, Qt::gray);
        }
    }

    return grid;
}

void Graphics::AddShape(Shape *s)
{
    qDebug() << "Add shape to list" << s;
    shapeList.append(s);
}

void Graphics::DeleteLastShape()
{
    if (!shapeList.isEmpty())
    {
        shapeList.pop_back();
        qDebug() << "Remove shape: ";
    }
    else
        qDebug() << "Shape list is empty";
}

void Graphics::SetShapes(QList<Shape *> s)
{
    shapeList = s;
}

void Graphics::Repaint()
{
    canvas.fill(Qt::transparent);
    foreach (Shape* s, shapeList)
    {
        s->Draw(canvas);
    }
}

QImage Graphics::DrawShape(Shape *shape)
{
    newShape.fill(Qt::transparent);
    if (shape)
        shape->Draw(newShape);
    return newShape;
}

void Graphics::DrawShape(Shape *shape, QImage& image)
{
    shape->Draw(image);
}

QList<Shape *> Graphics::GetShapes()
{
    return shapeList;
}

Shape *Graphics::GetShapeAt(QPoint point)
{
    Shape* s;
    for (int i=0;i<shapeList.length(); i++)
    {
        s = shapeList[i];
        if (s->GetRect().contains(point))
        {
            shapeList.removeAt(i);
            return s;
        }
    }
    s = shapeList.front();
    shapeList.pop_front();
    return s;
}
