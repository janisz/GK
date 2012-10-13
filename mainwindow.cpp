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
    gapSizeSpinBox->setMinimum(1);
    gapSizeSpinBox->setMaximum(600);
    gapSizeSpinBox->setValue(100);
    leftPanelLayout->addWidget(gapSizeSpinBox);

    colorChooseButton = new QPushButton(this);
    colorChooseButton->setText("Set Color");
    leftPanelLayout->addWidget(colorChooseButton);

    shapeChooserComboBox = new QComboBox(this);
    shapeChooserComboBox->addItems(shapeList);
    leftPanelLayout->addWidget(shapeChooserComboBox);

    testButton = new QPushButton("Test",  this);
    leftPanelLayout->addWidget(testButton);


    connect (showGridCheckBox, SIGNAL(clicked()), this, SLOT(ShowGrid()));
    connect (gapSizeSpinBox, SIGNAL(editingFinished()), this, SLOT(ShowGrid()));
    connect (gapSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ShowGrid()));
    connect (colorChooseButton, SIGNAL(clicked()), this, SLOT(ChangeColor()));
    connect (testButton, SIGNAL(clicked()), this, SLOT(RunTest()));
    connect (shapeChooserComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeShape()));

    setMouseTracking(true);
}

void MainWindow::RunTest()
{
    paintArea->RunTest();
}

void MainWindow::ChangeColor()
{
    paintArea->SetLineColor(QColorDialog::getColor(Qt::red, this ));
}

void MainWindow::ChangeShape()
{
    paintArea->SetCurrentShape((ShapeType)shapeChooserComboBox->currentIndex());
}

void MainWindow::ShowGrid()
{
    paintArea->SetGridVisibility(showGridCheckBox->isChecked());
    paintArea->SetGridGap(gapSizeSpinBox->value());
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
