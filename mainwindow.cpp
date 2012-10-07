#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    //Set constans and variables
    shapeList.append("Line");
    shapeList.append("Circle");

    //Create UI
    setFixedSize(1000, 620);
    setWindowTitle("Grafika Komputerowa");

    paintArea = new PaintArea(this);
    paintArea->show();

    leftPanelWidget = new QWidget(this);
    leftPanelWidget->setGeometry(800, 0, 200, 600);
    leftPanelLayout = new QVBoxLayout();
    leftPanelWidget->setLayout(leftPanelLayout);

    statusBar = new QStatusBar(this);
    statusBar->showMessage("Started working", 5);
    statusBar->setGeometry(0, 600, 100, 20);
    statusBar->show();

    showGridCheckBox = new QCheckBox(this);
    showGridCheckBox->setText("Show Grid");
    leftPanelLayout->addWidget(showGridCheckBox);

    gapSizeSpinBox = new QSpinBox(this);
    leftPanelLayout->addWidget(gapSizeSpinBox);

    colorChooseButton = new QPushButton(this);
    colorChooseButton->setText("Set Color");
    leftPanelLayout->addWidget(colorChooseButton);

    shapeChooserComboBox = new QComboBox(this);
    shapeChooserComboBox->addItems(shapeList);
    leftPanelLayout->addWidget(shapeChooserComboBox);


    setMouseTracking(true);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    statusBar->showMessage(QString("X:%1 \t Y:%2").arg(event->pos().x()).arg(event->pos().y()));
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    event->ignore();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

MainWindow::~MainWindow()
{
    
}
