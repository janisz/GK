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

    Engine en;
    en.readOff();
    QList<double*> l = en.Calculate();
    qDebug() << "Paint";
    foreach (double* point, l)
    {
        //qDebug() << point[0] << point[1] << point[2] << point[3];
        Circle *c = new Circle(QPoint((point[0]/point[3])*100.0+400.0, (point[1]/point[3])*100.0+300.0), 1, lineColor);
        c->SetColor(lineColor);
        Canvas.AddShape(c);
    }

//    DrawComb(100);
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



void PaintArea::SetCurrentFigureAtribiutes()
{
    if (!currentFigure) return;  
    currentFigure->SetColor(lineColor);
    currentFigure->isFilled = fillShape;
    currentFigure->SetTexture(texture);
    if (!Canvas.GetShapes().empty())
    {
        Shape* s = Canvas.GetShapes().at(0);
        s->SetTexture(texture);
        QPainter painter;
        painter.begin(this);
        painter.drawImage(0, 0, Canvas.DrawShape(s));
        painter.end();
    }
}



void PaintArea::AddLine(const int x0, const int x1, const int y0, const int y1)
{
    Canvas.AddShape(new Line(QPoint(x0, y0), QPoint(x1, y1), lineColor));
}

void PaintArea::RunTest()
{

}



