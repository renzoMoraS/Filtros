#include <iostream>
#include <string>
#include <chrono>
#include <stdlib.h>
#include <vector>
#include "filters.h"

using namespace std;
int main(int argc , char* argv[]){

	int filtro;
	int threading;
	int param1;
	int param2;
	string imgA;
	string imgB;
	int r = 0;
	int g = 0;
	int b = 0;
	int ct = 0;

	filtro = atoi(argv[1]);
	threading = atoi(argv[2]);

	pixel pix;
	pix.r = 0;
	pix.g = 0;
	pix.b = 0;

	if (filtro == 0 || filtro == 1 || filtro == 8 || filtro == 9){
		imgA = string(argv[3]);
	}else if (filtro == 2 || filtro == 3 || filtro == 4 || filtro == 5){
		param1 = atoi(argv[3]);
		imgA = string(argv[4]);
		if (filtro == 5){
			imgB = string(argv[5]);
		}	
	}else if (filtro == 6 || filtro == 7){
		param1 = atoi(argv[3]);
		param2 = atoi(argv[4]);
		imgA = string(argv[5]);
		if (filtro == 7){
			pix.r = param2;
			pix.g = param2;
			pix.b = param2;
		}
	}

	ppm img1(imgA);
	ppm img2(imgB);

	ppm imgzoomed(img1.width * 2,img1.height * 2);
	ppm imgzoomed2(img1.width * 2,img1.height * 2);
	ppm imgMo(img1.width,img1.height);

	switch (filtro){
	case 0:
		noFilter(img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 1:
		if (threading > 1){
			struct data data_in;
			data_in.filtro = "blackWhite1";
			data_in.n_threads = threading;
			ppm* imgt = &img1;
			data_in.img1 = imgt;
			thread_handler(data_in);
		}else{
			blackWhite(img1);
		}
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");	
		cout << "Listo" << endl;
		break;
	case 2:
		if (threading > 1){
			struct data data_in;
			data_in.filtro = "blackWhite2";
			data_in.p1 = param1;
			data_in.n_threads = threading;
			ppm* imgt = &img1;
			data_in.img1 = imgt;
			thread_handler(data_in);
		}else{
			blackWhite(img1,param1);
		}
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");			
		cout << "Listo" << endl;
		break;
	case 3:
		if (threading > 1){
			struct data data_in;
			data_in.filtro = "brightness";
			data_in.p1 = param1;
			data_in.n_threads = threading;
			ppm* imgt = &img1;
			data_in.img1 = imgt;
			thread_handler(data_in);
		}else{
			brightness(param1,img1);
		}
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 4:
		if (threading > 1){
			struct data data_in;
			data_in.filtro = "contrast";
			data_in.p1 = param1;
			data_in.n_threads = threading;
			ppm* imgt = &img1;
			data_in.img1 = imgt;
			thread_handler(data_in);
		}else{
			contrast(img1,param1);
		}
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 5:
		if (threading > 1){
			struct data data_in;
			data_in.filtro = "merge";
			data_in.p1 = param1;
			data_in.n_threads = threading;
			ppm* imgt = &img1;
			ppm* imgt2 = &img2;
			ppm* imgM = &imgMo;
			data_in.img1 = imgt;
			data_in.img2 = imgt2;
			data_in.imgM = imgM;
			thread_handler(data_in);
			cout << "Escribiendo imagen" << endl;
			imgMo.write("imgs/resultado.ppm");
			cout << "Listo" << endl;
		}else{
			merge(img1,img2,param1);
			cout << "Escribiendo imagen" << endl;
			img1.write("imgs/resultado.ppm");
			cout << "Listo" << endl;
		}
		break;
	case 6:
		crop(img1,param1,param2);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 7:
		frame(param1,pix,img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 8:
		if (threading > 1){
			struct data data_in;
			data_in.filtro = "boxBlur";
			data_in.n_threads = threading;
			ppm* imgt = &img1;
			data_in.img1 = imgt;
			thread_handler(data_in);
		}else{
			boxBlur(img1);
		}
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 9:
		if (threading > 1){
			struct data data_in;
			data_in.filtro = "zoom";
			data_in.n_threads = threading;
			ppm* imgt = &img1;
			ppm* imgt2 = &imgzoomed;
			ppm* imgt3 = &imgzoomed2;
			data_in.img1 = imgt;
			data_in.img2 = imgt2;
			data_in.imgM = imgt3;
			thread_handler(data_in);
			cout << "Escribiendo imagen" << endl;
			imgzoomed.write("imgs/resultado.ppm");
			cout << "Listo" << endl;
		}else{
			zoom(img1,imgzoomed);
			cout << "Escribiendo imagen" << endl;
			imgzoomed.write("imgs/resultado.ppm");
			cout << "Listo" << endl;
		}
		break;
	default:
		break;
	}
}