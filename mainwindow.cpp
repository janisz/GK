#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    //Set constans and variables
    shapeList.append("Line");
    shapeList.append("Circle");
    shapeList.append("AACircle");
    shapeList.append("Ellipse");
    shapeList.append("Polygon");
    shapeList.append("StrongLine");
    shapeList.append("StrongCircle");

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

    newLineButton = new QPushButton("Line", this);
    leftPanelLayout->addWidget(newLineButton);


    connect (showGridCheckBox, SIGNAL(clicked()), this, SLOT(ShowGrid()));
    connect (gapSizeSpinBox, SIGNAL(editingFinished()), this, SLOT(ShowGrid()));
    connect (gapSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ShowGrid()));
    connect (colorChooseButton, SIGNAL(clicked()), this, SLOT(ChangeColor()));
    connect (testButton, SIGNAL(clicked()), this, SLOT(RunTest()));
    connect (newLineButton, SIGNAL(clicked()), this, SLOT(NewLine()));
    connect (shapeChooserComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeShape()));

    setMouseTracking(true);
}

void MainWindow::RunTest()
{
    paintArea->RunTest();
}

void MainWindow::NewLine()
{
    int x0, y0, x1, y1;
    x0 = y0 = x1 = y1 = 0;

    x0 = QInputDialog::getInteger(this, "Insert value", "X0");
    y0 = QInputDialog::getInteger(this, "Insert value", "Y0");
    x1 = QInputDialog::getInteger(this, "Insert value", "X1");
    y1 = QInputDialog::getInteger(this, "Insert value", "Y1");

    paintArea->AddLine(x0, x1, y0, y1);
}

void MainWindow::ChangeColor()
{
    paintArea->SetLineColor(QColorDialog::getColor(Qt::red, this ));
}

void MainWindow::ChangeShape()
{
    paintArea->SetCurrentShape((Globals::ShapeType)shapeChooserComboBox->currentIndex());
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
