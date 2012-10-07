#include "paintarea.h"

PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    QImage newImage(800, 600, QImage::Format_ARGB32);
    image = newImage;
    Canvas.SetCanvas(image);
    setFixedSize(800, 600);
    ClearImage();
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
    repaint();
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
    if (startPoint == QPoint(0,0))
        return;
    Canvas.DrawLine(startPoint, event->pos(), Qt::red);
    image = Canvas.GetCanvas();
    update();
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0, 0, image);
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
