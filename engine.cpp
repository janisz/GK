#include "engine.h"

Engine::Engine()
{

}

double* Engine::MatrixMul(double* matrixA, double* matrixB, int Bsize)
{
    double* result = new double[4*Bsize];
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<Bsize; j++)
        {
            result[i*Bsize+j] = 0.0;
                for(int k=0; k<4; k++)
                {
                   result[i*Bsize+j] += matrixA[i*4+k] * matrixB[k*Bsize+j];
                }

        }
    }
    return result;
}

void Engine::readOff()
{
    QString fileName = QFileDialog::getOpenFileName();
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    QString line = in.readLine();
    qDebug() << line;
    line = in.readLine();
    QStringList fields = line.split(" ");
    qDebug() << fields;
    int vertexs = fields[0].toInt();
    int faces = fields[1].toInt();
    for (int i=0;i<vertexs;i++) {

        line = in.readLine();
        fields = line.split(" ");
        double* d = new double[4];
        d[0] = fields[0].toDouble(); d[1] = fields[1].toDouble(); d[2] = fields[2].toDouble(); d[3] = 1.0;
        qDebug() << d[0] << d[1] << d[2] << d[3];
        vertexsList.append(d);
        qDebug() << fields;
    }

    for (int i=0;i<vertexs;i++) {
        double* d = vertexsList[i];
        qDebug() << d[0] << d[1] << d[2] << d[3];
    }

    file.close();
}

QList<double*> Engine::Calculate()
{
    qDebug() << "Calculate";
    QList<double*> ret;
    double *res = MatrixMul(projectionMatrix, viewMatrix);
    foreach (double* point, vertexsList)
    {
        double* p1 = MatrixMul(res, point, 1);

        ret.append(p1);
    }

    return ret;
}