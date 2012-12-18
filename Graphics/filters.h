#ifndef FILTERS_H
#define FILTERS_H

#include <QImage>
#include <QRect>
#include <QColor>

class Filters
{
public:
    Filters();
    static QImage blurred(const QImage& image, const QRect& rect, int radius, bool alphaOnly);
    static QImage MatrixFilter(const QImage& image, double filter1[][3], int size, double factor, double bias);
    static QImage MatrixFilter(const QImage& image, double filter1[][5], int size, double factor, double bias);
    static QImage MatrixFilter(const QImage& image, double filter1[][7], int size, double factor, double bias);
};

#endif // FILTERS_H
