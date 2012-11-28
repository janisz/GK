#include "colors.h"

//D65

float *rgb2xyz(float r, float g, float b)
{
    float x, y, z;
    x =  0.4124f * r + 0.3576f * g + 0.1805f * b;
    y =  0.2126f * r + 0.7152f * g + 0.0721f * b;
    z =  0.0193f * r + 0.1192f * g + 0.9505f * b;
    float *result = new float[3];
    result[0] = x;
    result[1] = y;
    result[2] = z;
    return result;
}

float* xyz2rgb(float x, float y, float z)
{
    double dr,dg,db;
    float r, g, b;
//    dr =  0.32406  * x - 0.15371 * y - 0.049895 * z;
//    dg = -0.096891 * x + 0.18757 * y + 0.0041914* z;
//    db =  0.0055708* x - 0.020401* y + 0.1057   * z;

//    if(dr<=0.00313) dr=dr*12.92;
//    else dr=exp(log(dr)/2.4)*1.055-0.055;

//    if(dg<=0.00313) dg=dg*12.92;
//    else dg=exp(log(dg)/2.4)*1.055-0.055;

//    if(db<=0.00313) db=db*12.92;
//    else db=exp(log(db)/2.4)*1.055-0.055;

//    r= MIN(1.0f,MAX(0.0f,dr));
//    g= MIN(1.0f,MAX(0.0f,dg));
//    b= MIN(1.0f,MAX(0.0f,db));

    r =  3.240479*x - 1.537150*y - 0.498535*z;
    g = -0.969256*x + 1.875992*y + 0.041556*z;
    b =  0.055648*x - 0.204043*y + 1.057311*z;

//    if (r < 0 || g < 0 || b < 0)
//        r = g = b = 0;
//    if (r > 1 || g > 1 || b > 1)
//        r = g = b = 0;

    float *result = new float[3];
    result[0] = r;
    result[1] = g;
    result[2] = b;
    return result;
}

float* hsv2rgb(float hue, float sat, float val) {
        float red, grn, blu;
        float i, f, p, q, t;
        float *result = new float[3];

        if(val==0) {
                red = 0;
                grn = 0;
                blu = 0;
        } else {
                hue/=60;
                i = floor(hue);
                f = hue-i;
                p = val*(1-sat);
                q = val*(1-(sat*f));
                t = val*(1-(sat*(1-f)));
                if (i==0) {red=val; grn=t; blu=p;}
                else if (i==1) {red=q; grn=val; blu=p;}
                else if (i==2) {red=p; grn=val; blu=t;}
                else if (i==3) {red=p; grn=q; blu=val;}
                else if (i==4) {red=t; grn=p; blu=val;}
                else if (i==5) {red=val; grn=p; blu=q;}
        }
        result[0] = red;
        result[1] = grn;
        result[2] = blu;
        return result;
}

float *rgb2hsv(float red, float grn, float blu){
        float hue, sat, val;
        float x, f, i;
        float *result = new float[3];

        x = MIN(MIN(red, grn), blu);
        val = MAX(MAX(red, grn), blu);
        if (x == val){
                hue = 0;
                sat = 0;
        }
        else {
                f = (red == x) ? grn-blu : ((grn == x) ? blu-red : red-grn);
                i = (red == x) ? 3 : ((grn == x) ? 5 : 1);
                hue = fmod((i-f/(val-x))*60, 360);
                sat = ((val-x)/val);
        }
        result[0] = hue;
        result[1] = sat;
        result[2] = val;
        return result;
}



