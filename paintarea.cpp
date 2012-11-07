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
    texture = QImage(1, 1, QImage::Format_ARGB32);
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
    update();
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
    }
    update();
}



void PaintArea::paintEvent(QPaintEvent *event)
{
    SetCurrentFigureAtribiutes();
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
                qDebug() << "Convex: " << ((Polygon*)currentFigure)->isConvex();
                drawPolygon = false;
                return;
            }
            if (Canvas.GetShapes().isEmpty())
                return;
            currentFigure = Canvas.GetShapeAt(event->pos());
            dragShape = true;
            update();
        }
        break;
        case Qt::MiddleButton:
        {
            if (currentFigure &&
                currentFigure->GetType() == Globals::Polygon &&
                ((Polygon*)currentFigure)->isConvex())
            {
                Polygon::ClippingPolygon = ((Polygon*)currentFigure);
                return;
            }
            delete currentFigure;
            currentFigure = NULL;
            update();
        }
    }

}

void PaintArea::SetCurrentFigureAtribiutes()
{
    if (!currentFigure) return;
    currentFigure->SetColor(lineColor);
    currentFigure->isFilled = fillShape;
    currentFigure->SetTexture(texture);
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

void PaintArea::AddLine(const int x0, const int x1, const int y0, const int y1)
{
    Canvas.AddShape(new Line(QPoint(x0, y0), QPoint(x1, y1), lineColor));
}

void PaintArea::RunTest()
{

}



