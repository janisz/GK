#include <QtGui/QApplication>
#include "mainwindow.h"


Polygon* Shape::ClippingPolygon = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
