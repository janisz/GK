#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QtGui>
#include "Globals.h"
#include "Graphics/graphics.h"
#include "Graphics/polygon.h"
#include "Graphics/circle.h"
#include "Graphics/aacircle.h"
#include "Graphics/rectangle.h"
#include "Graphics/filters.h"
#include <cmath>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);
    
public:
    bool LoadImage(const QString &fileName);
    void SetLineColor(QColor);
    void SetGridVisibility(bool);
    void SetGridGap(int);
    void SetCurrentShape(Globals::ShapeType);
    void AddLine(const int x0, const int x1, const int y0, const int y1);
    void RunTest();
    void ChangeTexture(QImage img) {texture = img; SetCurrentFigureAtribiutes(); repaint();}
    void Fill(bool isFilled) {fillShape = isFilled; update();}
    void SetCurrentFigureAtribiutes();
    void DrawComb(int N);
    QImage getImageUnderRect();
    void StrechHistogram();
    void RotateImage(int angle);
    void MatrixFilter(double filter[], int size, int factor, int bias);
    void ScaleImage(float k);
    void GammaFilter(double gamma);
    QImage filteredImage;
    Globals::FilterType filterType = Globals::Scale;
    int scale = 1;
    int rotation = 0;
    double* matrixFilter = NULL;
    int matrixFilterSize = 3;
    double gammaValue = 1.0;

public slots:
    void ClearImage();

protected:
    void doFilter();
    void paintEvent(QPaintEvent* );
    void mouseMoveEvent(QMouseEvent* );
    void mousePressEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent *);

private:
    Graphics Canvas;

    QImage image;
    QImage bacground;
    QImage texture;
    bool fillShape;
    QColor lineColor;
    QPoint startPoint;
    Shape* currentFigure;
    bool showGrid;
    bool dragShape;
    int gridGap;
    bool drawPolygon;
    QList<QPoint> polygonPoints;
    Globals::ShapeType currentShape;
    Shape* DrawPolygon();
    Rectangle* filterArea;
    
};

#endif // PAINTAREA_H
