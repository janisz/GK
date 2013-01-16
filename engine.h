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

    static double *currentMatrix;

    double viewMatrix[16] = { 1,	0,	0,	0,
                              0,	-1,	0,	0,
                              0,	0,	1,	-10,
                              0,	0,	0,	1};

    double projectionMatrix[16] = {2.4142135624, 0,	0,	0,
                                   0,	2.4142135624,	0,	0,
                                   0,	0,	-1.0202020202,	-2.0202020202,
                                   0,	0,	-1,	0};


    double translationMatrix[16] = {   1, 0, 0, 0,
                                       0, 1, 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 0, 1 };


    double rotationX[16] = {   1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1 };

    double rotationY[16] = {   1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1 };

    double rotationZ[16] = {   1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               0, 0, 0, 1 };

    void Move(double x, double y, double z)
    {
        translationMatrix[3] = x;
        translationMatrix[7] = y;
        translationMatrix[11] = z;
    }

    void RotateZ(double z)
    {
        rotationZ[0] = cos(z);
        rotationZ[1] = -sin(z);
        rotationZ[4] = sin(z);
        rotationZ[5] = cos(z);
    }

    void RotateX(double z)
    {
        rotationX[5] = cos(z);
        rotationX[6] = -sin(z);
        rotationX[9] = sin(z);
        rotationX[10] = cos(z);
    }
    void RotateY(double z)
    {
        rotationY[0] = cos(z);
        rotationY[2] = sin(z);
        rotationY[8] = -sin(z);
        rotationY[10] = cos(z);
    }

    void Rotate(double x, double y, double z)
    {
        RotateX(x);
        RotateY(y);
        RotateZ(z);

    }

    QList<double*> vertexsList;
    int **facesList;
    int FacesCount;
    int VertexCount;

    void readOff();
    QList<double*> Calculate();

    static double* MatrixMul(double* matrixA, double* matrixB, int Bsize = 4);

};

#endif // ENGINE_H
