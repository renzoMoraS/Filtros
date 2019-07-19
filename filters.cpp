#include "filters.h"
#include <ctype.h>
#include <math.h>

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
	cout << "Applying merge..." << endl;

	p1 = p1/100;
	p2 = 1 - p1;

	for(int i=0;i<img1.height;i++){
		for(int j=0;j<img1.width;j++){
			int r = img2.bitmap[i][j].r;
			int g = img2.bitmap[i][j].g;
			int bl = img2.bitmap[i][j].b;
			pixel n;

			r = r * p1 + r * p2;
			g = g * p1 + g * p2 ;
			bl = bl * p1 + bl * p2;

			n.r = r;
			n.g = g;
			n.b = bl;

			setPixel(i,j,n,img1);
		}
	}	
	return;	
}

void brightness(float b, ppm& img){
	//TODO
	cout << "Applying brightness..." << endl;

	b = b/100;

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
	cout << "Aplicando frame..." << endl;

	int cont1 = x;
	int cont2 = x;
	ppm imgFrame(img.width + x * 2, img.height + x * 2);

	for(int i=0;i<imgFrame.height;i++){
		for(int j=0;j<imgFrame.width;j++){
			setPixel(i,j,color,imgFrame);
		}
	}

	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int b = img.bitmap[i][j].b;

			pixel n; 

			n.r = r;
			n.g = g;
			n.b = b;

			setPixel(cont1,cont2,n,imgFrame);
			cont2++;
		}
		cont1++;
		cont2 = x;
	}

	img = imgFrame;

	return;
}

void boxBlur(ppm &img){
	//TODO
	cout << "Applying bloxBlur..." << endl;

	int r;
	int g;
	int bl;

	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			if (i != 0 && i != img.height - 1 && j != 0 && j != img.width - 1){

				r = (img.bitmap[i + 1][j].r + img.bitmap[i][j + 1].r + img.bitmap[i - 1][j].r + img.bitmap[i][j - 1].r + img.bitmap[i + 1][j + 1].r + img.bitmap[i - 1][j - 1].r + img.bitmap[i + 1][j - 1].r + img.bitmap[i - 1][j + 1].r)/8;
				g = (img.bitmap[i + 1][j].g + img.bitmap[i][j + 1].g + img.bitmap[i - 1][j].g + img.bitmap[i][j - 1].g + img.bitmap[i + 1][j + 1].g + img.bitmap[i - 1][j - 1].g + img.bitmap[i + 1][j - 1].g + img.bitmap[i - 1][j + 1].g)/8;
				bl = (img.bitmap[i + 1][j].b + img.bitmap[i][j + 1].b + img.bitmap[i - 1][j].b + img.bitmap[i][j - 1].b + img.bitmap[i + 1][j + 1].b + img.bitmap[i - 1][j - 1].b + img.bitmap[i + 1][j - 1].b + img.bitmap[i - 1][j + 1].b)/8;

			} else if(i == 0 && j == 0)
			{
				r = (img.bitmap[i + 1][j].r + img.bitmap[i + 1][j + 1].r + img.bitmap[i][j + 1].r)/3;
				g = (img.bitmap[i + 1][j].g + img.bitmap[i + 1][j + 1].g + img.bitmap[i][j + 1].g)/3;
				bl = (img.bitmap[i + 1][j].b + img.bitmap[i + 1][j + 1].b + img.bitmap[i][j + 1].b)/3;

			} else if(i == img.height - 1 && j == 0)
			{
				r = (img.bitmap[i - 1][j].r + img.bitmap[i - 1][j + 1].r + img.bitmap[i][j + 1].r)/3;
				g = (img.bitmap[i - 1][j].g + img.bitmap[i - 1][j + 1].g + img.bitmap[i][j + 1].g)/3;
				bl = (img.bitmap[i - 1][j].b + img.bitmap[i - 1][j + 1].b + img.bitmap[i][j + 1].b)/3;

			} else if(i == 0 && j == img.width - 1)
			{
				r = (img.bitmap[i][j - 1].r + img.bitmap[i + 1][j - 1].r + img.bitmap[i + 1][j].r)/3;
				g = (img.bitmap[i][j - 1].g + img.bitmap[i + 1][j - 1].g + img.bitmap[i + 1][j].g)/3;
				bl = (img.bitmap[i][j - 1].b + img.bitmap[i + 1][j - 1].b + img.bitmap[i + 1][j].b)/3;

			} else if(i == img.height - 1 && j == img.width - 1)
			{
				r = (img.bitmap[i][j - 1].r + img.bitmap[i - 1][j - 1].r + img.bitmap[i][j - 1].r)/3;
				g = (img.bitmap[i][j - 1].g + img.bitmap[i - 1][j - 1].g + img.bitmap[i][j - 1].g)/3;
				bl = (img.bitmap[i][j - 1].b + img.bitmap[i - 1][j - 1].b + img.bitmap[i][j - 1].b)/3;

			} else if(i != 0 && j == 0)
			{
				r = (img.bitmap[i + 1][j].r + img.bitmap[i + 1][j + 1].r + img.bitmap[i][j + 1].r + img.bitmap[i - 1][j + 1].r + img.bitmap[i - 1][j].r)/5;
				g = (img.bitmap[i + 1][j].g + img.bitmap[i + 1][j + 1].g + img.bitmap[i][j + 1].g + img.bitmap[i - 1][j + 1].g + img.bitmap[i - 1][j].g)/5;
				bl = (img.bitmap[i + 1][j].b + img.bitmap[i + 1][j + 1].b + img.bitmap[i][j + 1].b + img.bitmap[i - 1][j + 1].b + img.bitmap[i - 1][j].b)/5;

			} else if(i != 0 && j == img.width - 1)
			{
				r = (img.bitmap[i + 1][j].r + img.bitmap[i + 1][j - 1].r + img.bitmap[i - 1][j].r + img.bitmap[i][j - 1].r + img.bitmap[i - 1][j - 1].r)/5;
				g = (img.bitmap[i + 1][j].g + img.bitmap[i + 1][j - 1].g + img.bitmap[i - 1][j].g + img.bitmap[i][j - 1].g + img.bitmap[i - 1][j - 1].g)/5;
				bl = (img.bitmap[i + 1][j].b + img.bitmap[i + 1][j - 1].b + img.bitmap[i - 1][j].b + img.bitmap[i][j - 1].b + img.bitmap[i - 1][j - 1].b)/5;
			
			} else if(i == 0 && j != 0)
			{
				r = (img.bitmap[i + 1][j].r + img.bitmap[i + 1][j - 1].r + img.bitmap[i][j + 1].r + img.bitmap[i][j - 1].r + img.bitmap[i + 1][j + 1].r)/5;
				g = (img.bitmap[i + 1][j].g + img.bitmap[i + 1][j - 1].g + img.bitmap[i][j + 1].g + img.bitmap[i][j - 1].g + img.bitmap[i + 1][j + 1].g)/5;
				bl = (img.bitmap[i + 1][j].b + img.bitmap[i + 1][j - 1].b + img.bitmap[i][j + 1].b + img.bitmap[i][j - 1].b + img.bitmap[i + 1][j + 1].b)/5;
			
			} else if(i == img.height - 1 && j != 0)
			{
				r = (img.bitmap[i - 1][j].r + img.bitmap[i][j - 1].r + img.bitmap[i][j + 1].r + img.bitmap[i - 1][j - 1].r + img.bitmap[i - 1][j + 1].r)/5;
				g = (img.bitmap[i - 1][j].g + img.bitmap[i][j - 1].g + img.bitmap[i][j + 1].g + img.bitmap[i - 1][j - 1].g + img.bitmap[i - 1][j + 1].g)/5;
				bl = (img.bitmap[i - 1][j].b + img.bitmap[i][j - 1].b + img.bitmap[i][j + 1].b + img.bitmap[i - 1][j - 1].b + img.bitmap[i - 1][j + 1].b)/5;
			}
			
			
			pixel n;

			n.r = r;
			n.g = g;
			n.b = bl;

			setPixel(i,j,n,img);
		}
	}	
	return;	
}

void zoom(ppm &img, ppm &img_zoomed){
	//TODO
	//Tener en cuenta que img_zoomed debe ser una imagen "vacia" previamente creada con el tamáño adecuado
	cout << "Aplicando zoom..." << endl;
	int newSize = sqrt(img_zoomed.size / img.size);
	int cont1 = 0;
	int cont2 = 0;

	for(int i=0;i<img.height;i++){
		cont2 = 0;
		for(int j=0;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int bl = img.bitmap[i][j].b;
			pixel n;

			n.r = r;
			n.g = g;
			n.b = bl;

			setPixel(cont1,cont2,n,img_zoomed);
			setPixel(cont1,cont2+1,n,img_zoomed);
			setPixel(cont1+1,cont2,n,img_zoomed);
			setPixel(cont1+1,cont2+1,n,img_zoomed);
			cont2 = cont2 + newSize;
		}
		cont1 = cont1 + newSize;
	}	

	return;	
}

void crop(ppm &img, int k, int t){
	cout << "Aplicando crop..." << endl;

	int cont1 = 0;
	int cont2 = 0;
	ppm imgCrop(img.width - k, img.height - t);

	for(int i=t+1;i<img.height;i++){
		for(int j=k+1;j<img.width;j++){
			int r = img.bitmap[i][j].r;
			int g = img.bitmap[i][j].g;
			int b = img.bitmap[i][j].b;

			pixel n; 

			n.r = r;
			n.g = g;
			n.b = b;

			setPixel(cont1,cont2,n,imgCrop);
			cont2++;
		}
		cont1++;
		cont2 = 0;
	}

	img = imgCrop;

	return;
}