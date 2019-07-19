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
	cout << "Ingresar id del filtro a utilizar: ";
	cin >> filtro;
	cout << endl;
	cout << "Ingresar id del tipo de threading: ";
	cin >> threading;
	cout << endl;

	if (filtro == 2 || filtro == 3 || filtro == 4 || filtro == 7){
		cout << "Ingresar primer parametro: ";
		cin >> param1;
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
		
	}

	if (filtro == 5 || filtro == 6){
		cout << "Ingresar primer parametro: ";
		cin >> param1;
		cout << endl;
		cout << "Ingresar segundo parametro: ";
		cin >> param2;
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

	pixel pix;
	pix.r = r;
	pix.g = g;
	pix.b = b;

	ppm imgzoomed(img1.width * 2,img1.height * 2);

	switch (filtro)
	{
	case 0:
		cout << "Aplicando filtro"<< endl;
		noFilter(img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 1:
		cout << "Aplicando filtro"<< endl;
		blackWhite(img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 2:
		cout << "Aplicando filtro"<< endl;
		blackWhite(img1,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 3:
		cout << "Aplicando filtro"<< endl;
		brightness(param1,img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");		
		cout << "Listo" << endl;
		break;
	case 4:
		cout << "Aplicando filtro"<< endl;
		contrast(img1,param1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 5:
		cout << "Aplicando filtro"<< endl;
		merge(img1,img2,param1,param2);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 6:
		cout << "Aplicando filtro"<< endl;
		crop(img1,param1,param2);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 7:
		cout << "Aplicando filtro"<< endl;
		frame(param1,pix,img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 8:
		cout << "Aplicando filtro"<< endl;
		boxBlur(img1);
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		break;
	case 9:
		cout << "Aplicando filtro"<< endl;
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
	// NO TERMINADO merge(img1,img2,30,70);
	// TERMINADO crop(img1,50,50);
	// TERMINADO frame(30,pix,img1);
	// TERMINADO boxBlur(img1);
	// TERMINADO zoom(img1,imgzoomed);