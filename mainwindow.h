#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "Globals.h"
#include "paintarea.h"
#include "Graphics/colors.h"
#include "Graphics/octree.h"
#include "Graphics/colorquantizer.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    
private:
    PaintArea *paintArea;
    QWidget* leftPanelWidget;
    QVBoxLayout* leftPanelLayout;
    QStatusBar *statusBar;
    QCheckBox *showGridCheckBox;
    QSpinBox *gapSizeSpinBox;
    QCheckBox *filledCheckBox;
    QPushButton *testButton;
    QSlider *translateX;
    QSlider *translateY;
    QSlider *translateZ;
    QSlider *rotateX;
    QSlider *rotateY;
    QSlider *rotateZ;


protected:
    void mouseMoveEvent(QMouseEvent *);
    void moveEvent(QMoveEvent *);

public:
    MainWindow(QWidget *parent = 0);
    QImage setPalete(int x);
    ~MainWindow();

public slots:
    void SetFill();
    void Rotate();
    void Translate();
};

#endif // MAINWINDOW_H
