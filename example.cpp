#include <iostream>
#include <string>
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

	filtro = atoi(argv[1]);
	threading = atoi(argv[2]);

	pixel pix;
	pix.r = 0;
	pix.g = 0;
	pix.b = 0;

	if (filtro == 0 || filtro == 1 || filtro == 8 || filtro == 9){
		imgA = string(argv[3]);
	}else if (filtro == 2 || filtro == 3 || filtro == 4 || filtro == 5|| filtro == 7){
		param1 = atoi(argv[3]);
		imgA = string(argv[4]);
		if (filtro == 5){
			imgB = string(argv[5]);
		}	
	}else if (filtro == 6){
		param1 = atoi(argv[3]);
		param2 = atoi(argv[4]);
		imgA = string(argv[5]);
	}

	ppm img1(imgA);
	ppm img2(imgB);
	ppm imgzoomed(img1.width * 2,img1.height * 2);

	switch (filtro){
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
		cout << "Listo" << endl;
		break;
	default:
		break;
	}
}