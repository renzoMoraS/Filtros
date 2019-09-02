#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <pthread.h>
#include "filters.h"
using namespace std;
int main(int argc , char* argv[]){

	int singlethread;
	int rc;
	int i;
	int multithread;
	int param1;
	int param2;
	string imgA;
	string imgB;
	int r = 0;
	int g = 0;
	int b = 0;

	singlethread = atoi(argv[1]);
	multithread = atoi(argv[2]);

	pixel pix;
	pix.r = 0;
	pix.g = 0;
	pix.b = 0;
	data d;
	if (singlethread == 0 || singlethread == 1 || singlethread == 8 || singlethread == 9){
		imgA = string(argv[3]);
	}else if (singlethread == 2 || singlethread == 3 || singlethread == 4 || singlethread == 5){
		param1 = atoi(argv[3]);
		imgA = string(argv[4]);
		if (singlethread == 5){
			imgB = string(argv[5]);
		}	
	}else if (singlethread == 6 ){
		param1 = atoi(argv[3]);
		param2 = atoi(argv[4]);
		imgA = string(argv[5]);
	}
	else if (singlethread == 7 ){
		param1 = atoi(argv[3]);
		param2 = atoi(argv[4]);
	}
	if (multithread == 0 || multithread == 7 || multithread == 8){
		imgA = string(argv[3]);
	}else if (multithread == 1 || multithread == 2 || multithread == 3 || multithread == 4|| multithread == 7){
		param1 = atoi(argv[3]);
		imgA = string(argv[4]);
		if (multithread == 5){
			imgB = string(argv[5]);
		}	
	}else if (singlethread == 5){
		param1 = atoi(argv[3]);
		param2 = atoi(argv[4]);
		imgA = string(argv[5]);
	}

	ppm img1(imgA);
	ppm img2(imgB);
	ppm imgzoomed(img1.width * 2,img1.height * 2);
	auto start = std::chrono::system_clock::now();
	switch (singlethread){
	case 0:
		noFilter(img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 1:
		blackWhite(img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 2:
		blackWhite(img1,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 3:
		brightness(param1,img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 4:
		contrast(img1,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 5:
		merge(img1,img2,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 6:
		crop(img1,param1,param2);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 7:
		frame(param1,pix,img1);
		pix.r = param1;
		pix.g = param1;
		pix.b = param1;
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 8:
		boxBlur(img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 9:
		zoom(img1,imgzoomed);
		cout << "Escribiendo imagen" << endl;
		imgzoomed.write("imgs/resultado.ppm");
		cout << "Listo" <<  endl;
		break;
	default:
		break;
	}
	/*switch (multithread){
	case 0:
		blackWhiteThread(img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 1:
		blackWhiteThread(img1,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 2:
		brightnessThread(param1,img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 3:
		contrastThread(img1,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 4:
		mergeThread(img1,img2,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 5:
		cropThread(img1,param1,param2);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 6:
		frameThread(param1,pix,img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 7:
		boxBlurThread(img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 8:
		zoomThread(img1,imgzoomed);
		cout << "Escribiendo imagen" << endl;
		imgzoomed.write("imgs/resultado.ppm");
		cout << "Listo" <<  endl;
		break;
	default:
		break;
	}
	 */
}