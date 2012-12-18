#include "paintarea.h"


PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    QImage newImage(800, 600, QImage::Format_ARGB32);
    image = newImage;
    filterArea = new Rectangle(QRect(0, 0, 800, 600));
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



QImage PaintArea::getImageUnderRect()
{
    QRect rect =  filterArea->GetRect();
    return Canvas.GetCanvas().copy(rect);
}

void PaintArea::DrawComb(int N)
{
    Polygon *comb = new Polygon();
    comb->AddVertex(QPoint(5*N, 5));
    comb->AddVertex(QPoint(5*N, 0));
    comb->AddVertex(QPoint(0, 0));
    comb->AddVertex(QPoint(0, 5));
    for (int i=0;i<N;i++)
    {
        comb->AddVertex(QPoint(i*5+2, (N-i+1)*5));
        comb->AddVertex(QPoint(i*5+5, 5));
    }
    comb->SetColor(lineColor);
    comb->SetTexture(texture);
    comb->isFilled = fillShape;
    Canvas.AddShape(comb);

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
    if (dragShape && currentShape == Globals::Rectangle)
    {
        filterArea->Move(event->pos() - mousePos);
        update();
    }
    else if (dragShape)
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
        case Globals::StrongLine:
        currentFigure = new Line(startPoint, event->pos(), lineColor, 5);
        break;
        case Globals::Circle:
        currentFigure = new Circle(QPoint(startPoint.x()+r*sgn(e.x()), startPoint.y()+r*sgn(e.y())), std::abs(r), lineColor);
        break;
        case Globals::AACircle:
        currentFigure = new AACircle(QPoint(startPoint.x()+r*sgn(e.x()), startPoint.y()+r*sgn(e.y())), std::abs(r), lineColor);
        break;
        case Globals::Rectangle:
        currentFigure = new Rectangle(QRect(startPoint, mousePos));
        break;
    }
    update();
}

float* MatrixMultiplication(float x[2][2], float y[])
{
    int length = 2;
    float *answer = new float[length];

    for (int i = 0; i < length; ++i)
        answer[i] = 0;

    for (int i = 0; i < length; ++i)
        for (int j = 0; j < length; ++j)
            answer[i] += (float)(x[i][ j] * y[j]);

    return answer;
}

void PaintArea::RotateImage(int angle)
{
    qDebug() << angle;
    filteredImage = getImageUnderRect();

    int x = filteredImage.width();
    int y = filteredImage.height();


    QImage rotatedImage(x, y, QImage::Format_ARGB32);
    rotatedImage.fill(Qt::black);

    int x0 =  x / 2;
    int y0 =  y / 2;

    double an = angle * 2 * M_PI / 360;

    float matrix[2][2] = {{ cos(an), -sin(an)},
                          { sin(an),  cos(an)}};

    for (int i = 0; i < x ; ++i)
        for (int j = 0; j < y ; ++j)
        {
            float *vector = new float[2];
            vector[0] = i-x0;
            vector[1] = j-y0;

            vector = MatrixMultiplication(matrix, vector);

            vector[0] += x0;
            vector[1] += y0;
            if (0 <= vector[0] && vector[0] < x &&
                    0 <= vector[1] && vector[1] < y &&  filteredImage.pixel((int)vector[0], (int)vector[1]))
                rotatedImage.setPixel(i, j, filteredImage.pixel((int)vector[0], (int)vector[1]) );
        }

    filteredImage = rotatedImage;
    update();
}



void PaintArea::MatrixFilter(double filter[], int size, int factor, int bias)
{
    filteredImage = getImageUnderRect();
    filteredImage = Filters::MatrixFilter(filteredImage, filter, 3, factor, bias);
    update();
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    SetCurrentFigureAtribiutes();
    QPainter *painter = new QPainter(this);
    painter->begin(this);
    painter->drawImage(0, 0 , bacground);
    painter->drawImage(0, 0, Canvas.GetCanvas());
    painter->drawImage(0, 0, Canvas.DrawShape(currentFigure));
    painter->drawImage(0, 0, Canvas.DrawShape(filterArea));
    painter->drawImage(filterArea->GetRect(), filteredImage);
    painter->end();
    delete painter;
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    drawPolygon = (currentShape == Globals::Polygon);
    switch (event->button())
    {
        case Qt::LeftButton:
        {
            if ((!currentFigure ||
                 currentFigure->GetType() != Globals::Polygon || ((Polygon*)currentFigure)->isFinish) && drawPolygon)
            {
                currentFigure = new Polygon();
                currentFigure->SetColor(lineColor);
            }           
            if (drawPolygon && currentFigure && currentFigure->GetType() == Globals::Polygon && !((Polygon*)currentFigure)->isFinish )
            {
                ((Polygon*)currentFigure)->AddVertex(event->pos());
            }
            if (currentShape == Globals::Rectangle)
            {
                Canvas.GetShapes().removeAll(filterArea);
            }
            startPoint = event->pos();
        }
        break;
        case Qt::RightButton:
        {
            if (drawPolygon && currentFigure->GetType() == Globals::Polygon)
            {
                qDebug() << "Convex: " << ((Polygon*)currentFigure)->isConvex();
                drawPolygon = false;
                ((Polygon*)currentFigure)->isFinish = true;
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
    if (!Canvas.GetShapes().empty())
    {
        Shape* s = Canvas.GetShapes().at(0);
        s->SetTexture(texture);

    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (drawPolygon)
        return;

    dragShape = false;
    startPoint = QPoint(0,0);

    if (currentFigure && currentFigure->GetType() == Globals::Rectangle)
    {
        filterArea = (Rectangle*)currentFigure;
        return;
    }

    if (currentFigure)
        Canvas.AddShape(currentFigure);
}

void PaintArea::AddLine(const int x0, const int x1, const int y0, const int y1)
{
    Canvas.AddShape(new Line(QPoint(x0, y0), QPoint(x1, y1), lineColor));
}

void PaintArea::RunTest()
{

}



