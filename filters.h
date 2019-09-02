#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "ppm.h"
#define BLACK 0

struct data{
    string filtro; 
	unsigned char n_threads;
	ppm *img1;
	ppm *img2;
	ppm *imgM;
	float p1;
	float p2;
	unsigned char tid;
};

//USEFUL FUNCTIONS
unsigned char truncate(int color);
void setPixel(int i, int j, pixel p, ppm& img);


//FILTERS

void* blackWhiteT(void* data);
void* blackWhiteT2(void* data);
void* contrastT(void* data);
void* brightnessT(void* data);
void* mergeT(void* data);
void* boxBlurT(void* data);
void* zoomT(void* data);


void thread_handler(data& d);
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