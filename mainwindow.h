#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "paintarea.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    
private:
    PaintArea *paintArea;
    QStatusBar *statusBar;

protected:
    void mouseMoveEvent(QMouseEvent *);
    void moveEvent(QMoveEvent *);
    void mousePressEvent(QMouseEvent *);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
