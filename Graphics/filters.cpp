#include "filters.h"

Filters::Filters()
{

}

QImage Filters::MatrixFilter(const QImage& image, double filter[][3], int size, double factor, double bias)
{
    int filterWidth = size;
    int filterHeight = size;

    int w = image.width();
    int h = image.height();

    QImage result = image;

    for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
    {
        double red = 0.0, green = 0.0, blue = 0.0;

        for(int filterX = 0; filterX < filterWidth; filterX++)
        for(int filterY = 0; filterY < filterHeight; filterY++)
        {
            int imageX = (x - filterWidth / 2 + filterX + w) % w;
            int imageY = (y - filterHeight / 2 + filterY + h) % h;
            red += qRed(image.pixel(imageX, imageY)) * filter[filterX][filterY];
            green += qGreen(image.pixel(imageX, imageY)) * filter[filterX][filterY];
            blue += qBlue(image.pixel(imageX, imageY)) * filter[filterX][filterY];
        }

        int r, g, b;
        r = std::min(std::max(int(factor * red + bias), 0), 255);
        g = std::min(std::max(int(factor * green + bias), 0), 255);
        b = std::min(std::max(int(factor * blue + bias), 0), 255);

        result.setPixel(x, y, qRgb(r, g, b));
    }

    return result;

}

QImage Filters::MatrixFilter(const QImage& image, double filter[][5], int size, double factor, double bias)
{
    int filterWidth = size;
    int filterHeight = size;

    int w = image.width();
    int h = image.height();

    QImage result = image;

    for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
    {
        double red = 0.0, green = 0.0, blue = 0.0;

        for(int filterX = 0; filterX < filterWidth; filterX++)
        for(int filterY = 0; filterY < filterHeight; filterY++)
        {
            int imageX = (x - filterWidth / 2 + filterX + w) % w;
            int imageY = (y - filterHeight / 2 + filterY + h) % h;
            red += qRed(image.pixel(imageX, imageY)) * filter[filterX][filterY];
            green += qGreen(image.pixel(imageX, imageY)) * filter[filterX][filterY];
            blue += qBlue(image.pixel(imageX, imageY)) * filter[filterX][filterY];
        }

        int r, g, b;
        r = std::min(std::max(int(factor * red + bias), 0), 255);
        g = std::min(std::max(int(factor * green + bias), 0), 255);
        b = std::min(std::max(int(factor * blue + bias), 0), 255);

        result.setPixel(x, y, qRgb(r, g, b));
    }

    return result;

}

QImage Filters::MatrixFilter(const QImage& image, double filter[][7], int size, double factor, double bias)
{
    int filterWidth = size;
    int filterHeight = size;

    int w = image.width();
    int h = image.height();

    QImage result = image;

    for(int x = 0; x < w; x++)
    for(int y = 0; y < h; y++)
    {
        double red = 0.0, green = 0.0, blue = 0.0;

        for(int filterX = 0; filterX < filterWidth; filterX++)
        for(int filterY = 0; filterY < filterHeight; filterY++)
        {
            int imageX = (x - filterWidth / 2 + filterX + w) % w;
            int imageY = (y - filterHeight / 2 + filterY + h) % h;
            red += qRed(image.pixel(imageX, imageY)) * filter[filterX][filterY];
            green += qGreen(image.pixel(imageX, imageY)) * filter[filterX][filterY];
            blue += qBlue(image.pixel(imageX, imageY)) * filter[filterX][filterY];
        }

        int r, g, b;
        r = std::min(std::max(int(factor * red + bias), 0), 255);
        g = std::min(std::max(int(factor * green + bias), 0), 255);
        b = std::min(std::max(int(factor * blue + bias), 0), 255);

        result.setPixel(x, y, qRgb(r, g, b));
    }

    return result;

}

QImage Filters::blurred(const QImage& image, const QRect& rect, int radius, bool alphaOnly = false)
{
int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
int alpha = (radius < 1) ? 16 : (radius > 17) ? 1 : tab[radius-1];

QImage result = image.convertToFormat(QImage::Format_ARGB32);
int r1 = rect.top();
int r2 = rect.bottom();
int c1 = rect.left();
int c2 = rect.right();

int bpl = result.bytesPerLine();
int rgba[4];
unsigned char* p;

int i1 = 0;
int i2 = 3;

if (alphaOnly)
i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

for (int col = c1; col <= c2; col++) {
p = result.scanLine(r1) + col * 4;
for (int i = i1; i <= i2; i++)
rgba[i] = p[i] << 4;

p += bpl;
for (int j = r1; j < r2; j++, p += bpl)
for (int i = i1; i <= i2; i++)
p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
}

for (int row = r1; row <= r2; row++) {
p = result.scanLine(row) + c1 * 4;
for (int i = i1; i <= i2; i++)
rgba[i] = p[i] << 4;

p += 4;
for (int j = c1; j < c2; j++, p += 4)
for (int i = i1; i <= i2; i++)
p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
}

for (int col = c1; col <= c2; col++) {
p = result.scanLine(r2) + col * 4;
for (int i = i1; i <= i2; i++)
rgba[i] = p[i] << 4;

p -= bpl;
for (int j = r1; j < r2; j++, p -= bpl)
for (int i = i1; i <= i2; i++)
p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
}

for (int row = r1; row <= r2; row++) {
p = result.scanLine(row) + c2 * 4;
for (int i = i1; i <= i2; i++)
rgba[i] = p[i] << 4;

p -= 4;
for (int j = c1; j < c2; j++, p -= 4)
for (int i = i1; i <= i2; i++)
p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
}

return result;
}
