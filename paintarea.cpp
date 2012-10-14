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
    dragShape = false;
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
    currentFigure.SetColor(color);
    update();
}

void PaintArea::SetCurrentShape(ShapeType shape)
{
    currentShape = shape;
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
    static QPoint mousePos;
    if (dragShape)
    {
        QPointList pl;
        foreach (QPoint p, currentFigure.GetPoints())
        {
            p.setX(p.x() - mousePos.x() + event->pos().x());
            p.setY(p.y() - mousePos.y() + event->pos().y());
            pl.append(p);
        }
        currentFigure.SetPoints(pl);
        update();
    }
    mousePos = event->pos();

    if (startPoint == QPoint(0,0))
        return; 

    Shape s;
    QPoint e = event->pos()-startPoint;
    int r = std::max(e.x(), e.y()) / 2;
    switch (currentShape)
    {
        case Line:
            s = Canvas.DrawLine(startPoint, event->pos(), lineColor);
        break;
        case Circle:
            s = Canvas.Circle(QPoint(startPoint.x()+r, startPoint.y()+r), std::abs(r), lineColor);
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
    switch (event->button())
    {
        case Qt::LeftButton:
            startPoint = event->pos();
        break;
        case Qt::RightButton:
        {

            if (Canvas.GetShapes().isEmpty())
                return;
            currentFigure = Canvas.GetShapeAt(event->pos());
            currentFigure.SetColor(lineColor);
            dragShape = true;
            update();
        }
        break;
    }

}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (!currentFigure.GetPoints().isEmpty())
        Canvas.AddShape(currentFigure);
    currentFigure = Shape();
    dragShape = false;
    startPoint = QPoint(0,0);
}

void PaintArea::RunTest()
{
    long int N = 500000;
    QTime myTimer;
    myTimer.start();
    Shape s;
    QImage img = bacground;
    img.fill(Qt::black);
    for (long int i=0;i<N;i++)
    {
         (Canvas.DrawLine(0, 0, 800, 600, Qt::blue, img));
    }
    int nMilliseconds = myTimer.elapsed();
    qDebug() << nMilliseconds/1000;
    bacground = img;
    update();
}



