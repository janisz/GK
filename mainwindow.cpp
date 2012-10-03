#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    //Create UI
    setFixedSize(1000, 620);
    setWindowTitle("Grafika Komputerowa");

    paintArea = new PaintArea(this);
    paintArea->show();

    statusBar = new QStatusBar(this);
    statusBar->showMessage("Started working", 5);
    statusBar->setGeometry(0, 600, 1000, 20);
    statusBar->show();

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
