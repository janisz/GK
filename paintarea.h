#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QtGui>

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
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QImage image;
    bool showGrid;
    
};

#endif // PAINTAREA_H
