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

template <typename T> int sgn(T val) {
    return (T(0) <= val) - (val < T(0));
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if (currentShape == Polygon)
    {
        drawPolygon = true;
        return;
    }
    else drawPolygon = false;

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
        currentFigure.SetPoints(pl, currentFigure.GetAlpha());
        update();
    }
    mousePos = event->pos();

    if (startPoint == QPoint(0,0))
        return; 

    Shape s;
    QPoint e = event->pos()-startPoint;
    int r = std::sqrt(e.x()*e.x()+e.y()*e.y()) * std::sqrt(2) / 4;
    switch (currentShape)
    {
        case Line:
            s = Canvas.DrawLine(startPoint, event->pos(), lineColor);
        break;
        case Circle:
            s = Canvas.Circle(QPoint(startPoint.x()+r*sgn(e.x()), startPoint.y()+r*sgn(e.y())), std::abs(r), lineColor);
        break;
        case AACircle:
        s = (Canvas.AACircle(QPoint(startPoint.x()+r*sgn(e.x()), startPoint.y()+r*sgn(e.y())), std::abs(r), lineColor));
        break;
        case Ellipse:
            s = Canvas.Ellipse(startPoint, event->pos(), lineColor);
        break;
        case StrongLine:
            s = Canvas.DrawLine(startPoint, event->pos(), lineColor, 5);
        break;
        case StrongCircle:
            s = Canvas.Circle(QPoint(startPoint.x()+r*sgn(e.x()), startPoint.y()+r*sgn(e.y())), std::abs(r), lineColor, 3);
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

Shape PaintArea::DrawPolygon()
{
    QPointList points;
    QPoint prev = polygonPoints[0];

    for (int i=1;i<polygonPoints.size();i++)
    {
        points.append(Canvas.DrawLine(prev, polygonPoints[i], lineColor).GetPoints());
        prev = polygonPoints[i];
    }
    points.append(Canvas.DrawLine(polygonPoints.first(), polygonPoints.last(), lineColor).GetPoints());
    return Shape(points, lineColor);
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
        {
            if (drawPolygon)
            {
                startPoint = QPoint(1,1);
                polygonPoints.append(event->pos());
            }
            else
                startPoint = event->pos();
        }
        break;
        case Qt::RightButton:
        {
            if (drawPolygon)
            {
                currentFigure = DrawPolygon();
                drawPolygon = false;
                polygonPoints.clear();
                update();
                return;
            }
            if (Canvas.GetShapes().isEmpty())
                return;
            currentFigure = Canvas.GetShapeAt(event->pos());
            currentFigure.SetColor(lineColor);
            dragShape = true;
            drawPolygon = false;
            update();
        }
        break;
        case Qt::MiddleButton:
        {
            currentFigure = Shape();
            update();
        }
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
    for (long int i=0;i<N;i++)
    {
         Canvas.AddShape(Canvas.DrawLine(0, 0, 800, 600, Qt::blue));
    }
    int nMilliseconds = myTimer.elapsed();
    qDebug() << nMilliseconds/1000;
    update();
}



