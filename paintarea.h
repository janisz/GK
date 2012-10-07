#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QtGui>
#include "Graphics/graphics.h"

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);
    
public:
//    bool SaveImage(const QString &fileName, const char *fileFormat);
    bool LoadImage(const QString &fileName);

public slots:
    void ClearImage();
//    void ShowGrid();

protected:
    void paintEvent(QPaintEvent* );
    void mouseMoveEvent(QMouseEvent* );
    void mousePressEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent *);

private:
    QImage image;
    bool showGrid;
    Graphics Canvas;
    QPoint startPoint;
    
};

#endif // PAINTAREA_H
