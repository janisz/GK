#include "paintarea.h"


PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    QImage newImage(800, 600, QImage::Format_ARGB32);
    image = newImage;
    currentShape = Globals::Line;
    bacground = newImage;
    lineColor = Qt::red;
    ClearImage();
    setFixedSize(800, 600);
    dragShape = false;
    setMouseTracking(true);
    currentFigure = 0;
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
    if (currentFigure)
        currentFigure->SetColor(color);
    update();
}

void PaintArea::SetCurrentShape(Globals::ShapeType shape)
{
    currentShape = shape;
}

template <typename T> int sgn(T val) {
    return (T(0) <= val) - (val < T(0));
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
    static QPoint mousePos;
    if (dragShape)
    {
        if (currentFigure)
            currentFigure->Move(event->pos() - mousePos);
        update();
    }
    mousePos = event->pos();

    if (startPoint == QPoint(0,0))
        return;

    QPoint e = event->pos()-startPoint;
    int r = std::sqrt(e.x()*e.x()+e.y()*e.y()) * std::sqrt(2) / 4;
    switch (currentShape)
    {
        case Globals::Line:
        currentFigure = new Line(startPoint, event->pos(), lineColor);
        break;
    case Globals::Polygon:
        {

        }
    }
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
        {
            if (!currentFigure || !currentFigure->GetType() == Globals::Polygon)
            {
                currentFigure = new Polygon();
                currentFigure->SetColor(lineColor);
            }
            ((Polygon*)currentFigure)->AddVertex(event->pos());
            drawPolygon = (currentShape == Globals::Polygon);
            startPoint = event->pos();
        }
        break;
        case Qt::RightButton:
        {
            if (drawPolygon)
            {
                drawPolygon = false;
                return;
            }
            if (Canvas.GetShapes().isEmpty())
                return;
            currentFigure = Canvas.GetShapeAt(event->pos());
            currentFigure->SetColor(lineColor);
            dragShape = true;
            update();
        }
        break;
        case Qt::MiddleButton:
        {
            currentFigure = NULL;
            update();
        }
    }

}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (drawPolygon)
        return;

    if (currentFigure)
        Canvas.AddShape(currentFigure);
    currentFigure = NULL;
    dragShape = false;
    startPoint = QPoint(0,0);
}

void PaintArea::RunTest()
{
//    long int N = 500000;
//    QTime myTimer;
//    myTimer.start();
//    Shape s;
//    for (long int i=0;i<N;i++)
//    {
//         Canvas.AddShape(Canvas.DrawLine(0, 0, 800, 600, Qt::blue));
//    }
//    int nMilliseconds = myTimer.elapsed();
//    qDebug() << nMilliseconds/1000;
//    update();
}



