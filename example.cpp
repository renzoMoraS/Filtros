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

	cout << "FILTROS" << endl;
	cout << "0: No Filter" << endl;
	cout << "1: Black & White" << endl;
	cout << "2: GrayScale" << endl;
	cout << "3: Brightness" << endl;
	cout << "4: Contrast" << endl;
	cout << "5: Merge" << endl;
	cout << "6: Crop" << endl;
	cout << "7: Frame" << endl;
	cout << "8: Box Blur" << endl;
	cout << "9: Zoom" << endl;
	cout << endl;

	cout << "Ingresar id del filtro a utilizar: ";
	cin >> filtro;
	cout << endl;
	cout << "Ingresar id del tipo de threading (no terminado, no poner nada): ";
	cin >> threading;
	cout << endl;


	if (filtro == 7){
		cout << "Ingresar red: ";
		cin >> r;
		cout << endl;
		cout << "Ingresar green: ";
		cin >> g;
		cout << endl;
		cout << "Ingresar blue: ";
		cin >> b;
		cout << endl;
	}

	cout << "Ingresar imagen a utilizar: ";
	cin >> imgA;
	cout << endl;

	if (filtro == 5){
		cout << "Ingresar segunda imagen a utilizar: ";
		cin >> imgB;
		cout << endl;
	}

	ppm img1(imgA);
	ppm img2(imgB);
	ppm imgzoomed(img1.width * 2,img1.height * 2);

	pixel pix;
	pix.r = r;
	pix.g = g;
	pix.b = b;

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
		cout << "Ingresar cantidad de grises (0,255): ";
		cin >> param1;
		blackWhite(img1,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 3:
		cout << "Ingresar porcentaje de brillo (0,100): ";
		cin >> param1;
		brightness(param1,img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 4:
		cout << "Ingresar factor de intensidad de contraste (-255,255): ";
		cin >> param1;
		contrast(img1,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 5:
		cout << "Ingresar porcentaje de mezclado de la primer imagen (0,100): ";
		cin >> param1;
		merge(img1,img2,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 6:
		cout << "Ingresar k filas a cortar: ";
		cin >> param1;
		cout << "Ingresar t filas a cortar: ";
		cin >> param2;
		crop(img1,param1,param2);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 7:
		cout << "Ingresar tamaño del frame en pixeles: ";
		cin >> param1;
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

	// TERMINADO noFilter(img1);
	// TERMINADO blackWhite(img1);
	// TERMINADO blackWhite(img1,8);
	// TERMINADO brightness(200,img1);
	// TERMINADO contrast(img1,-200);
	// TERMINADO merge(img1,img2,30,70);
	// TERMINADO crop(img1,50,50);
	// TERMINADO frame(30,pix,img1);
	// TERMINADO boxBlur(img1);
	// TERMINADO zoom(img1,imgzoomed);