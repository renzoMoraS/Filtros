#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <pthread.h>
#include "filters.h"
#define NUM_THREADS 2
using namespace std;
int main(int argc , char* argv[]){

	int singlethread;
	int i;
	int multithread;
	int param1;
	int param2;
	string imgA;
	string imgB;
	int r = 0;
	int g = 0;
	int b = 0;

	pthread_t threads[NUM_THREADS];

	singlethread = atoi(argv[1]);
	multithread = atoi(argv[2]);

	pixel pix;
	pix.r = 0;
	pix.g = 0;
	pix.b = 0;

	if (singlethread == 0 || singlethread == 1 || singlethread == 8 || singlethread == 9){
		imgA = string(argv[3]);
	}else if (singlethread == 2 || singlethread == 3 || singlethread == 4 || singlethread == 5|| singlethread == 7){
		param1 = atoi(argv[3]);
		imgA = string(argv[4]);
		if (singlethread == 5){
			imgB = string(argv[5]);
		}	
	}else if (singlethread == 6){
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
		for( i = 0; i < NUM_THREADS; i++ ) {
      	cout << "Creando threads: " << i << endl;
      	pthread_create(&threads[i], NULL, noFilter(img1), (void *)i);
		}
		cout << "Escribiendo imagen" << endl;
		img1.write("imgs/resultado.ppm");
		cout << "Listo" << endl;
		pthread_exit(NULL);
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
		cout << "Listo" <<  endl;
		break;
	default:
		break;
	}
	 */
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "Le tomo ejecutarse: " << elapsed_seconds.count() << " segundos" << endl;
}