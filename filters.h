#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "ppm.h"
#define BLACK 0

struct data{
    unsigned char nthreads;
    ppm *img1;
    float param1;
    float param2;
    unsigned char thid;
};
//USEFUL FUNCTIONS
unsigned char truncate(int color);
void setPixel(int i, int j, pixel p, ppm& img);


//FILTERS

void blackWhite(ppm& img);
void contrast(ppm& img, float contrast);
void blackWhite(ppm& img, unsigned char shades);
void merge(ppm& img1, ppm& img2, float p1);
void brightness(float b, ppm& img);
void frame(int x, pixel color, ppm& img);
void boxBlur(ppm &img);
void zoom(ppm &img, ppm &img_zoomed);
void crop(ppm &img, int k, int t);
void noFilter(ppm& img);