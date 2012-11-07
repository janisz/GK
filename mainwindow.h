#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "Globals.h"
#include "paintarea.h"

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
    QPushButton *colorChooseButton;
    QPushButton *fillColorChooseButton;
    QPushButton *textureChooseButton;
    QCheckBox *filledCheckBox;
    QPushButton *testButton;
    QPushButton *newLineButton;
    QComboBox *shapeChooserComboBox;

    QStringList shapeList;

protected:
    void mouseMoveEvent(QMouseEvent *);
    void moveEvent(QMoveEvent *);
    void mousePressEvent(QMouseEvent *);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void ChangeColor();
    void ChangeFillColor();
    void ChangeFillTexture();
    void SetFill();
    void ChangeShape();
    void NewLine();
    void ShowGrid();
    void RunTest();

};

#endif // MAINWINDOW_H
