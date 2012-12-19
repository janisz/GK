#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "Globals.h"
#include "paintarea.h"
#include "Graphics/colors.h"
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
    QPushButton *colorChooseButton;
    QPushButton *fillColorChooseButton;
    QPushButton *textureChooseButton;
    QPushButton *doMatrixFilter;
    QCheckBox *filledCheckBox;
    QPushButton *testButton;
    QPushButton *strechHistogramButton;
    QPushButton *newLineButton;
    QPushButton *gaussianButton;
    QComboBox *shapeChooserComboBox;
    QComboBox *colorModelComboBox;
    QLabel *colorMap;
    QSpinBox **colorValueEdit;
    QSlider *colorIntensivitySlider;
    QSlider *colorCountSlider;
    QSlider *angleSlider;
    QSlider *scaleSlider;
    QStringList shapeList;
    QImage colorMapImage;
    QColor selectedColor;
    QSpinBox* matrixSize;
    QDoubleSpinBox* matrix;


protected:
    void mouseMoveEvent(QMouseEvent *);
    void moveEvent(QMoveEvent *);
    void mousePressEvent(QMouseEvent *);

public:
    MainWindow(QWidget *parent = 0);
    QImage setPalete(int x);
    void DrawHistogram();
    ~MainWindow();

public slots:
    void SetGaussMatrix();
    void ChangeColor();
    void MatrixFilter();
    void ChangeMatrixSize();
    void strechHistogram();
    void ChangeFillColor();
    void MoveSlider();
    void ChangeColorSpinBox();
    void ClickOnColorLabel();
    void ChangeFillTexture();
    void ChangeFillTextureColors();
    void SetFill();
    void ChangeShape();
    void NewLine();
    void ShowGrid();
    void RunTest();
    void ChangePalette();
    void ChangeLineColor();
    void ChangeAngle();
    void ChangeScale();
};

#endif // MAINWINDOW_H
