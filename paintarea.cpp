#include "paintarea.h"


PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    QImage newImage(800, 600, QImage::Format_ARGB32);
    image = newImage;
    lineColor = Qt::red;
    ClearImage();
    setFixedSize(800, 600);
    setMouseTracking(true);
}

bool PaintArea::LoadImage(const QString &fileName)
{
    QImage newImage;
    if (!newImage.load(fileName))
        return false;
    image = newImage;
    update();
    return true;
}

void PaintArea::ClearImage()
{
    image.fill(qRgb(0, 0, 0));
    Canvas.SetCanvas(image);
    repaint();
}

void PaintArea::SetGridGap(int gap)
{
    gridGap = gap;
    ClearImage();
    if (showGrid)
        Canvas.DrawGrid(gridGap);
    update();
}

void PaintArea::SetGridVisibility(bool visible)
{
    showGrid = visible;
    ClearImage();
}

void PaintArea::SetLineColor(QColor color)
{
    lineColor = color;
}

void PaintArea::SetCurrentShape(Shape shape)
{
    currentShape = shape;
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
    if (startPoint == QPoint(0,0))
        return;

    Canvas.DrawLine(startPoint, event->pos(), lineColor);
    Canvas.Circle(startPoint, (event->pos()-startPoint).manhattanLength(), lineColor);


    image = Canvas.GetCanvas();
    update();
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0, 0, Canvas.GetCanvas());
    painter.end();
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    startPoint = event->pos();
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    startPoint = QPoint(0,0);
}
