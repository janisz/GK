#ifndef ENGINE_H
#define ENGINE_H

#include <QMatrix>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QtGui>

class Engine
{
public:
    Engine();

    double viewMatrix[16] = {0,	1,	0,	-0.5,
                          0,	0,	1,	-0.5,
                          1,	0,	0,	-3,
                          0,	0,	0,	 1};
    double projectionMatrix[16] = {1.4281480067,	0,	0,	0,
                                0,	1.4281480067,	0,	0,
                                0,	0,	-1.0202020202,	-2.0202020202,
                                0,	0,	-1,	0};
    QList<double*> vertexsList;

    void readOff();
    QList<double*> Calculate();

    static double* MatrixMul(double* matrixA, double* matrixB, int Bsize = 4);

};

#endif // ENGINE_H
