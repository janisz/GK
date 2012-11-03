#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QtGui>
#include "Globals.h"
#include "Graphics/graphics.h"
#include "Graphics/polygon.h"
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
    void RunTest();

public slots:
    void ClearImage();

protected:
    void paintEvent(QPaintEvent* );
    void mouseMoveEvent(QMouseEvent* );
    void mousePressEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent *);

private:
    Graphics Canvas;
    QImage image;
    QImage bacground;
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
    
};

#endif // PAINTAREA_H
