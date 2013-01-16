#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    //Create UI
    setFixedSize(1010, 630);
    setWindowTitle("Grafika Komputerowa");

    leftPanelWidget = new QWidget(this);
    leftPanelWidget->setGeometry(800, 0, 210, 630);
    leftPanelLayout = new QVBoxLayout();
    leftPanelWidget->setLayout(leftPanelLayout);

    statusBar = new QStatusBar(this);
    statusBar->showMessage("Started working", 5);
    statusBar->setGeometry(0, 600, 100, 20);
    statusBar->show();

    filledCheckBox = new QCheckBox("Fill", this);
    leftPanelLayout->addWidget(filledCheckBox);

    paintArea = new PaintArea(this);
    paintArea->show();

    QLabel *translateLabel = new QLabel("Translate");
    leftPanelLayout->addWidget(translateLabel);

    translateX = new QSlider(Qt::Horizontal);
    translateX->setMaximum(800);
    translateX->setMinimum(-800);

    leftPanelLayout->addWidget(translateX);

    translateY = new QSlider(Qt::Horizontal);
    translateY->setMaximum(800);
    translateY->setMinimum(-800);
    leftPanelLayout->addWidget(translateY);

    translateZ = new QSlider(Qt::Horizontal);
    translateZ->setMaximum(800);
    translateZ->setMinimum(-800);
    leftPanelLayout->addWidget(translateZ);

    QLabel *rotateLabel = new QLabel("Rotate");
    leftPanelLayout->addWidget(rotateLabel);

    rotateX = new QSlider(Qt::Horizontal);
    rotateX->setMaximum(360);
    rotateX->setMinimum(0);
    leftPanelLayout->addWidget(rotateX);

    rotateY = new QSlider(Qt::Horizontal);
    rotateY->setMaximum(360);
    rotateY->setMinimum(0);
    leftPanelLayout->addWidget(rotateY);

    rotateZ = new QSlider(Qt::Horizontal);
    rotateZ->setMaximum(360);
    rotateZ->setMinimum(0);
    leftPanelLayout->addWidget(rotateZ);

    connect (filledCheckBox, SIGNAL(clicked()), this, SLOT(SetFill()));
    connect (translateX, SIGNAL(sliderMoved(int)), this, SLOT(Translate()));
    connect (translateY, SIGNAL(sliderMoved(int)), this, SLOT(Translate()));
    connect (translateZ, SIGNAL(sliderMoved(int)), this, SLOT(Translate()));

    connect (rotateX, SIGNAL(sliderMoved(int)), this, SLOT(Rotate()));
    connect (rotateY, SIGNAL(sliderMoved(int)), this, SLOT(Rotate()));
    connect (rotateZ, SIGNAL(sliderMoved(int)), this, SLOT(Rotate()));

    setMouseTracking(true);

}


void MainWindow::Translate()
{
    paintArea->Translate(translateX->value(), translateY->value(), translateZ->value());
}

void MainWindow::Rotate()
{
    paintArea->Rotate(rotateX->value(), rotateY->value(), rotateZ->value());
}

void MainWindow::SetFill()
{
    paintArea->Fill(filledCheckBox->isChecked());
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    statusBar->showMessage(QString("X:%1 \t Y:%2").arg(event->pos().x()).arg(event->pos().y()));
}

void MainWindow::moveEvent(QMoveEvent *event)
{


}


MainWindow::~MainWindow()
{
    
}
