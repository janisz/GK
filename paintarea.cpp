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

double* countNormals(float point11, float point12, float point13,
                   float point21, float point22, float point23,
                   float point31, float point32, float point33)
{
    double* Normal = new double[3];
float Vector1[3];
float Vector2[3];

// wyznaczanie wektorow....
Vector1[0]= point11-point21;
Vector1[1]= point12-point22;
Vector1[2]= point13-point23;

Vector2[0]= point21-point31;
Vector2[1]= point22-point32;
Vector2[2]= point23-point33;

//wyznaczanie normalnych....
Normal[0]=Vector1[1]*Vector2[2]- Vector1[2]*Vector2[1];
Normal[1]=Vector1[2]*Vector2[0]- Vector1[0]*Vector2[2];
Normal[2]=Vector1[0]*Vector2[1]- Vector1[1]*Vector2[0];

return Normal;
}

double dot(double* a, double* b) {
    return(a[0]*b[0] + a[1]*b[1] + a[2]*b[2]);
}


void PaintArea::paintEvent(QPaintEvent *event)
{
    SetCurrentFigureAtribiutes();
    Canvas.Clear();
    QList<double*> l = engine.Calculate();
    int orientation[engine.FacesCount];
    foreach (double* point, l)
    {
        point[0] = (point[0]/point[3])*100.0+400.0;
        point[1] = (point[1]/point[3])*100.0+300.0;
        point[2] = (point[2]/point[3])*100.0;

    }

    for (int i=0;i<800;i++)
        for (int j=0;j<600;j++)
        {
            Polygon::zBuffer[i][j] = 10000;
        }
        for (int i=0;i<engine.FacesCount;i++)
        {
            //back face culling
            double* N = countNormals(l[engine.facesList[i][0]][0], l[engine.facesList[i][0]][1], l[engine.facesList[i][0]][1],
                                    l[engine.facesList[i][1]][0], l[engine.facesList[i][1]][1], l[engine.facesList[i][1]][1],
                                    l[engine.facesList[i][2]][0], l[engine.facesList[i][2]][1], l[engine.facesList[i][2]][1]);
            double cameraTarget[3] = {-l[engine.facesList[i][0]][0],
                                      -l[engine.facesList[i][0]][1],
                                      1000-l[engine.facesList[i][0]][2]};
            double sin = dot(cameraTarget, N);
            if (dot(cameraTarget, N) <= 0) {
                delete N;
                continue;
            }
            delete N;

            if (l[engine.facesList[i][0]][2] < 10 || l[engine.facesList[i][1]][2] < 10 || l[engine.facesList[i][2]][2] < 10)
                continue;

            QPoint v1(l[engine.facesList[i][0]][0], l[engine.facesList[i][0]][1]);
            QPoint v2(l[engine.facesList[i][1]][0], l[engine.facesList[i][1]][1]);
            QPoint v3(l[engine.facesList[i][2]][0], l[engine.facesList[i][2]][1]);
            Polygon *c = new Polygon();
            c->AddVertex(v1, l[engine.facesList[i][0]][2]);
            c->AddVertex(v2, l[engine.facesList[i][1]][2]);
            c->AddVertex(v3, l[engine.facesList[i][2]][2]);
            c->SetColor(Qt::white);
            QImage col = QImage(5,5, QImage::Format_ARGB32);
            col.fill(QColor::fromHsv(qrand() % 256, 255, (190 * sin/100000 > 220 ? 240 : 190 * sin/100000 + 20)));
            c->SetTexture(col);
            c->isFilled = fillShape;
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



