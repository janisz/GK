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

    connect (filledCheckBox, SIGNAL(clicked()), this, SLOT(SetFill()));


    setMouseTracking(true);

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
