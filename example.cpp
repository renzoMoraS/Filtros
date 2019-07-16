#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "filters.h"

using namespace std;
int main(int argc , char* argv[]){

	cout << "Probando procesamiento de imagenes ppm" << endl;
	string img_1= "imgs/nausicaa2.ppm";
	ppm img1(img_1);
	cout << "Aplicando filtro"<< endl;
	//noFilter(img1);
	contrast(img1,-200);
	cout << "Escribiendo imagen" << endl;
	img1.write("imgs/resultado.ppm");		
	cout << "Listo" << endl;
}