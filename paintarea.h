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
    void AddLine(const int x0, const int x1, const int y0, const int y1);
    void RunTest();
    void ChangeTexture(QImage img) {texture = img; update();}
    void Fill(bool isFilled) {fillShape = isFilled; update();}
    void SetCurrentFigureAtribiutes();
    void DrawComb(int N);

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
    
};

#endif // PAINTAREA_H
