#ifndef COLORS_H
#define COLORS_H

#include <cmath>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

float* rgb2hsv(float red, float grn, float blu);
float* hsv2rgb(float hue, float sat, float val);
float* xyz2rgb(float x, float y, float z);
float* rgb2xyz(float r, float g, float b);

inline int get_bit(int decimal, int N)
{
    N = 32-N;
  return decimal & (1 << (N-1));
}

inline int getRed(unsigned int rgb)
{
    return (rgb)&0xFF;
}

inline int getGreen(unsigned int rgb)
{
    return (rgb>>8)&0xFF;
}
inline int getBlue(unsigned int rgb)
{
    return (rgb>>16)&0xFF;
}

#endif // COLORS_H
