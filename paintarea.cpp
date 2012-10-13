#include "paintarea.h"


PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    QImage newImage(800, 600, QImage::Format_ARGB32);
    image = newImage;
    currentShape = Line;
    bacground = newImage;
    lineColor = Qt::red;
    ClearImage();
    setFixedSize(800, 600);
    setMouseTracking(true);
    Canvas.SetCanvas(QImage(800, 600, QImage::Format_ARGB32));
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
    bacground.fill(qRgb(0, 0, 0));
}

void PaintArea::SetGridGap(int gap)
{
    gridGap = gap;
    if (showGrid)
        bacground = Canvas.DrawGrid(gridGap);
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

void PaintArea::SetCurrentShape(ShapeType shape)
{
    currentShape = shape;
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
    if (startPoint == QPoint(0,0))
        return;

    Shape s;

    switch (currentShape)
    {
        case Line:
            s = Canvas.DrawLine(startPoint, event->pos(), lineColor);
        break;
        case Circle:
            s = Canvas.Circle(startPoint, (event->pos()-startPoint).manhattanLength(), lineColor);
        break;
    }

    currentFigure = s;
    update();
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0, 0 , bacground);
    painter.drawImage(0, 0, Canvas.GetCanvas());
    painter.drawImage(0, 0, Canvas.DrawShape(currentFigure));
    painter.end();
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    startPoint = event->pos();
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (!currentFigure.GetPoints().empty())
        Canvas.AddShape(currentFigure);
    currentFigure = Shape();
    startPoint = QPoint(0,0);
}
