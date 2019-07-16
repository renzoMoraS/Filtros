#include "filters.h"

//USEFUL FUNCTIONS
void setPixel(int i, int j, pixel p, ppm& img){
	img.bitmap[i][j] = p;
	return;
}

unsigned char truncate(int color){
	//TODO
	if(color > 255){
		color = 255;
	} else if(color < 0) {
		color = 0;
	}
	return color;
}

//FILTERS

void noFilter(ppm& img){
	cout << "Applying noFilter..." << endl;
	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			setPixel(i,j,img.bitmap[i][j],img);
		}
	}	
	return;
}

void blackWhite(ppm& img){
	//TODO
	cout << "Applying blackWhite..." << endl;
	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int b = img.bitmap[i][j].b;
			int gray = (r + g + b)/3;
			pixel n; 
			n.r = gray;
			n.g = gray;
			n.b = gray;
			setPixel(i,j,n,img);
		}
	}	
	return;
}

void contrast(ppm& img, float contrast){
	//TODO
		cout << "Applying contrast..." << endl;
	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int bl = img.bitmap[i][j].b;
			pixel n;

			r = ((259*(contrast + 255))/(255*(259 - contrast)))*(r - 128) + 128;
			g = ((259*(contrast + 255))/(255*(259 - contrast)))*(g - 128) + 128;
			bl = ((259*(contrast + 255))/(255*(259 - contrast)))*(bl - 128) + 128;

			n.r = truncate(r);
			n.g = truncate(g);
			n.b = truncate(bl);

			setPixel(i,j,n,img);
		}
	}	
	return;	
}

void blackWhite(ppm& img, unsigned char shades){
	//TODO
	cout << "Applying blackWhite2..." << endl;
	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int b = img.bitmap[i][j].b;
			int gray = (r + g + b)/3;
			int rango = 255/shades;
			int gray2 = (gray/rango)*rango; 
			pixel n; 
			n.r = gray2;
			n.g = gray2;
			n.b = gray2;

			setPixel(i,j,n,img);
		}
	}	
	return;
}

void merge(ppm& img1, ppm& img2, float p1, float p2){
	//TODO
}
void brightness(float b, ppm& img){
	//TODO
	cout << "Applying brightness..." << endl;
	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int bl = img.bitmap[i][j].b;
			pixel n;

			r = r + 255 * b;
			g = g + 255 * b;
			bl = bl + 255 * b;

			n.r = truncate(r);
			n.g = truncate(g);
			n.b = truncate(bl);

			setPixel(i,j,n,img);
		}
	}	
	return;	
}

void frame(int x, pixel color, ppm& img){
	//TODO
}

void boxBlur(ppm &img){
	//TODO
}

void zoom(ppm &img, ppm &img_zoomed){
	//TODO
	//Tener en cuenta que img_zoomed debe ser una imagen "vacia" previamente creada con el tamáño adecuado
}