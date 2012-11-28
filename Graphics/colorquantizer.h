#ifndef COLORQUANTIZER_H
#define COLORQUANTIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

namespace Colors {

typedef struct {
    int w, h;
    unsigned char *pix;
} image_t, *image;

void color_quant(image im, int n_colors, int dither);
int write_ppm(image im, char *fn);
image read_ppm(const char *);
void Initialize();

inline void Quantize(const char fileName[], int colorCount)
{
    Initialize();
    image im = read_ppm(fileName);
    color_quant(im, colorCount, 0);
    write_ppm(im, "out.ppm");
    free(im);

}

//inline unsigned char* Quantize(unsigned char* pix, int w, int h, int colorCount)
//{
//    Initialize();
//    image im = (image)malloc(sizeof(image_t));;
//    im->pix = pix;
//    im->w = w;
//    im->h = h;
//    color_quant(im, colorCount, 0);
//    write_ppm(im, "out1x.ppm");
//    return im->pix;

//}
}

#endif // COLORQUANTIZER_H
