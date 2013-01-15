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


    engine.readOff();
    QList<double*> l = engine.Calculate();
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

void PaintArea::Translate(int x, int y, int z)
{
    engine.Move(x/100.0, y/100.0, z/100.0);
    update();
}

void PaintArea::Rotate(int x, int y, int z)
{
    qDebug() << x << y << z;
    engine.Rotate(x*M_PI/180, y*M_PI/180, z*M_PI/180);
    update();
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
    Canvas.Clear();
    QList<double*> l = engine.Calculate();
    foreach (double* point, l)
    {
        point[0] = (point[0]/point[3])*100.0+400.0;
        point[1] = (point[1]/point[3])*100.0+300.0;
    }
        for (int i=0;i<engine.FacesCount;i++)
        {

            QPoint v1(l[engine.facesList[i][0]][0], l[engine.facesList[i][0]][1]);
            QPoint v2(l[engine.facesList[i][1]][0], l[engine.facesList[i][1]][1]);
            QPoint v3(l[engine.facesList[i][2]][0], l[engine.facesList[i][2]][1]);
            Polygon *c = new Polygon();
            c->AddVertex(v1);
            c->AddVertex(v2);
            c->AddVertex(v3);
            c->SetColor(lineColor);
            Canvas.AddShape(c);
        }
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



