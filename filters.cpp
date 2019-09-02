#include "filters.h"
#include <ctype.h>
#include <math.h>
#include <pthread.h>
#include <chrono>

//USEFUL FUNCTIONS

void thread_handler(data& d){
	data threads_data[d.n_threads]; //arreglo de struct data
	pthread_attr_t attr;

	void* datap = &d;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_t threads[d.n_threads]; 
	
	for(int i = 0; i<d.n_threads;i++){
		threads_data[i] = d;
		threads_data[i].tid = i; 
		if (d.filtro == "blackWhite1"){
			pthread_create(&threads[i],&attr,blackWhiteT,(void*)&threads_data[i]);
		}else if (d.filtro == "blackWhite2"){
			pthread_create(&threads[i],&attr,blackWhiteT2,(void*)&threads_data[i]);
		}else if (d.filtro == "brightness"){
			pthread_create(&threads[i],&attr,brightnessT,(void*)&threads_data[i]);
		}else if (d.filtro == "contrast"){
			pthread_create(&threads[i],&attr,contrastT,(void*)&threads_data[i]);
		}else if (d.filtro == "merge"){
			pthread_create(&threads[i],&attr,mergeT,(void*)&threads_data[i]);
		}else if (d.filtro == "boxBlur"){
			pthread_create(&threads[i],&attr,boxBlurT,(void*)&threads_data[i]);
		}else if (d.filtro == "zoom"){
			pthread_create(&threads[i],&attr,zoomT,(void*)&threads_data[i]);
		}
		
	}
	
	pthread_attr_destroy(&attr);

    for(int p=0; p<d.n_threads; p++){
		cout << "Esperando Thread " << p + 1 << endl;
        pthread_join(threads[p], NULL);
    }
 	printf("Filtro terminado\n");
 	return;

}

void setPixelT(int i, int j, pixel p, ppm* img){
	img->bitmap[i][j] = p;
	return;
}

void setPixel(int i, int j, pixel p, ppm& img){
	img.bitmap[i][j] = p;
	return;
}

unsigned char truncate(int color){
	
	if(color > 255){
		color = 255;
	} else if(color < 0) {
		color = 0;
	}
	return color;
}

//FILTERS

void noFilter(ppm& img){
	cout << "Aplicando noFilter..." << endl;
	for(int i=0;i<img.height;i++){
		for(int j=0;j<img.width;j++){
			setPixel(i,j,img.bitmap[i][j],img);
		}
	}	
	return;
}

void blackWhite(ppm& img){
	//TODO
	cout << "Aplicando blackWhite..." << endl;
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
	cout << "Aplicando contrast..." << endl;
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
	cout << "Aplicando blackWhite2..." << endl;
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

void merge(ppm& img1, ppm& img2, float p1){
	//TODO
	cout << "Aplicando merge..." << endl;

	p1 = p1/100;
	float p2 = 1 - p1;

	ppm imgMerge(img1.width,img1.height);

	for(int i=0;i<img1.height;i++){
		for(int j=0;j<img1.width;j++){

			int r1 = img1.bitmap[i][j].r;
			int g1 = img1.bitmap[i][j].g;
			int bl1 = img1.bitmap[i][j].b;

			int r2 = img2.bitmap[i][j].r;
			int g2 = img2.bitmap[i][j].g;
			int bl2 = img2.bitmap[i][j].b;
			pixel n;

			int r = r1 * p1 + r2 * p2;
			int g = g1 * p1 + g2 * p2;
			int bl = bl1 * p1 + bl2 * p2;

			r = truncate(r);
			g = truncate(g);
			bl = truncate(bl);

			n.r = r;
			n.g = g;
			n.b = bl;

			setPixel(i,j,n,imgMerge);
		}
	}	

	img1 = imgMerge; 

	return;	
}

void brightness(float b, ppm& img){
	//TODO
	cout << "Aplicando brightness..." << endl;

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
	cout << "Aplicando bloxBlur..." << endl;

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
	int newSize = img_zoomed.height / img.height;
	cout << newSize;
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

			if (newSize == 2){
				setPixel(cont1,cont2+1,n,img_zoomed);
				setPixel(cont1+1,cont2,n,img_zoomed);
				setPixel(cont1+1,cont2+1,n,img_zoomed);	
			}else if(newSize == 3){
				setPixel(cont1,cont2+1,n,img_zoomed);
				setPixel(cont1+1,cont2,n,img_zoomed);
				setPixel(cont1+1,cont2+1,n,img_zoomed);
				setPixel(cont1,cont2+2,n,img_zoomed);
				setPixel(cont1+2,cont2,n,img_zoomed);
				setPixel(cont1+2,cont2+1,n,img_zoomed);
				setPixel(cont1+1,cont2+2,n,img_zoomed);
				setPixel(cont1+2,cont2+2,n,img_zoomed);
			}	
			
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

//THREADS FILTERS

void* blackWhiteT(void* data){

	//casteo el parametro de entrada
	struct data* my_data;
	my_data = (struct data *) data;
	cout << "Applying black&White filter con..." << (int) my_data->n_threads <<  endl; // cuando tenemos punteros a struct, sus miembros se refieren con -> en vez de .


	//Calculo de limites
	ppm *img = my_data->img1;

	int interval = img->width/my_data->n_threads;

	int start = 0;

	if (my_data->tid == 0)
	{
		start = 0;
	}else
	{
		start = interval * my_data->tid;
	}
	
	int end = start + interval;

	//Algoritmo en si
	if (my_data->tid == 0){
		for(int i=start;i<end;i++){
			for(int j=0;j<img->width;j++){
				int r = img->bitmap[i][j].r;
				int g = img->bitmap[i][j].g;
				int b = img->bitmap[i][j].b;
				int gray = (r + g + b)/3;
				pixel n; 
				n.r = gray;
				n.g = gray;
				n.b = gray;
				setPixelT(i,j,n,img);
			}
		}
	}else{
		for(int i=start;i<end;i++){
			for(int j=0;j<img->width;j++){
				int r = img->bitmap[i][j].r;
				int g = img->bitmap[i][j].g;
				int b = img->bitmap[i][j].b;
				int gray = (r + g + b)/3;
				pixel n; 
				n.r = gray;
				n.g = gray;
				n.b = gray;
				setPixelT(i,j,n,img);
			}
		}
	}
	
	pthread_exit(NULL);

}

void* blackWhiteT2(void* data){

	//casteo el parametro de entrada
	struct data* my_data;
	my_data = (struct data *) data;
	cout << "Applying black&White2 filter con..." << (int) my_data->n_threads <<  endl; // cuando tenemos punteros a struct, sus miembros se refieren con -> en vez de .


	//Calculo de limites
	ppm *img = my_data->img1;

	int param1 = my_data->p1; 

	int interval = img->width/my_data->n_threads;

	int start = 0;

	if (my_data->tid == 0)
	{
		start = 0;
	}else
	{
		start = interval * my_data->tid;
	}
	
	int end = start + interval;

	//Algoritmo en si
	for(int i=start;i<end;i++){
		for(int j=0;j<img->width;j++){
			int r = img->bitmap[i][j].r;
			int g = img->bitmap[i][j].g;
			int b = img->bitmap[i][j].b;
			int gray = (r + g + b)/3;
			int rango = 255/param1;
			int gray2 = (gray/rango)*rango; 
			pixel n; 
			n.r = gray2;
			n.g = gray2;
			n.b = gray2;
			setPixelT(i,j,n,img);
		}
	}
	
	pthread_exit(NULL);
}

void* brightnessT(void* data){

	struct data* my_data;
	my_data = (struct data *) data;
	cout << "Applying brightnessT filter con..." << (int) my_data->n_threads <<  endl; // cuando tenemos punteros a struct, sus miembros se refieren con -> en vez de .


	//Calculo de limites
	ppm *img = my_data->img1;

	float param1 = my_data->p1; 

	int interval = img->width/my_data->n_threads;

	int start = 0;

	if (my_data->tid == 0)
	{
		start = 0;
	}else
	{
		start = interval * my_data->tid;
	}
	
	int end = start + interval;

	param1 = param1/100;

	for(int i=start;i<end;i++){
		for(int j=0;j<img->width;j++){
			int r = img->bitmap[i][j].r;
			int g = img->bitmap[i][j].g;
			int bl = img->bitmap[i][j].b;
			pixel n;

			r = r + 255 * param1;
			g = g + 255 * param1;
			bl = bl + 255 * param1;

			n.r = truncate(r);
			n.g = truncate(g);
			n.b = truncate(bl);

			setPixelT(i,j,n,img);
		}
	}

	pthread_exit(NULL);

}


void* contrastT(void* data){

	struct data* my_data;
	my_data = (struct data *) data;
	cout << "Applying contrastT filter con..." << (int) my_data->n_threads <<  endl; // cuando tenemos punteros a struct, sus miembros se refieren con -> en vez de .


	//Calculo de limites
	ppm *img = my_data->img1;

	float param1 = my_data->p1; 

	int interval = img->width/my_data->n_threads;

	int start = 0;

	if (my_data->tid == 0)
	{
		start = 0;
	}else
	{
		start = interval * my_data->tid;
	}
	
	int end = start + interval;

	for(int i=start;i<end;i++){
		for(int j=0;j<img->width;j++){
			int r = img->bitmap[i][j].r;
			int g = img->bitmap[i][j].g;
			int bl = img->bitmap[i][j].b;
			pixel n;

			r = ((259*(param1 + 255))/(255*(259 - param1)))*(r - 128) + 128;
			g = ((259*(param1 + 255))/(255*(259 - param1)))*(g - 128) + 128;
			bl = ((259*(param1 + 255))/(255*(259 - param1)))*(bl - 128) + 128;

			n.r = truncate(r);
			n.g = truncate(g);
			n.b = truncate(bl);

			setPixelT(i,j,n,img);
		}
	}	

	pthread_exit(NULL);
}

void* mergeT(void* data){

	struct data* my_data;
	my_data = (struct data *) data;
	cout << "Applying mergeT filter con..." << (int) my_data->n_threads <<  endl; // cuando tenemos punteros a struct, sus miembros se refieren con -> en vez de .


	//Calculo de limites
	ppm *img = my_data->img1;
	ppm *img2 = my_data->img2;

	float param1 = my_data->p1; 
	param1 = param1/100;
	float p2 = 1 - param1;

	int interval = img->width/my_data->n_threads;

	int start = 0;

	if (my_data->tid == 0)
	{
		start = 0;
	}else
	{
		start = interval * my_data->tid;
	}
	
	int end = start + interval;

	for(int i=start;i<end;i++){
		for(int j=0;j<img->width;j++){

			int r1 = img->bitmap[i][j].r;
			int g1 = img->bitmap[i][j].g;
			int bl1 = img->bitmap[i][j].b;

			int r2 = img2->bitmap[i][j].r;
			int g2 = img2->bitmap[i][j].g;
			int bl2 = img2->bitmap[i][j].b;
			pixel n;

			int r = r1 * param1 + r2 * p2;
			int g = g1 * param1 + g2 * p2;
			int bl = bl1 * param1 + bl2 * p2;

			r = truncate(r);
			g = truncate(g);
			bl = truncate(bl);

			n.r = r;
			n.g = g;
			n.b = bl;

			setPixelT(i,j,n,my_data->imgM);
		}
	}	

	img = my_data->imgM; 

	pthread_exit(NULL);
}

void* boxBlurT(void* data){

	struct data* my_data;
	my_data = (struct data *) data;
	cout << "boxBlurT filter con..." << (int) my_data->n_threads <<  endl; // cuando tenemos punteros a struct, sus miembros se refieren con -> en vez de .


	//Calculo de limites
	ppm *img = my_data->img1;

	int interval = img->width/my_data->n_threads;

	int start = 0;

	if (my_data->tid == 0)
	{
		start = 0;
	}else
	{
		start = interval * my_data->tid;
	}
	
	int end = start + interval;

	int r;
	int g;
	int bl;

	for(int i=start;i<end;i++){
		for(int j=0;j<img->width;j++){
			if (i != 0 && i != img->height - 1 && j != 0 && j != img->width - 1){

				r = (img->bitmap[i + 1][j].r + img->bitmap[i][j + 1].r + img->bitmap[i - 1][j].r + img->bitmap[i][j - 1].r + img->bitmap[i + 1][j + 1].r + img->bitmap[i - 1][j - 1].r + img->bitmap[i + 1][j - 1].r + img->bitmap[i - 1][j + 1].r)/8;
				g = (img->bitmap[i + 1][j].g + img->bitmap[i][j + 1].g + img->bitmap[i - 1][j].g + img->bitmap[i][j - 1].g + img->bitmap[i + 1][j + 1].g + img->bitmap[i - 1][j - 1].g + img->bitmap[i + 1][j - 1].g + img->bitmap[i - 1][j + 1].g)/8;
				bl = (img->bitmap[i + 1][j].b + img->bitmap[i][j + 1].b + img->bitmap[i - 1][j].b + img->bitmap[i][j - 1].b + img->bitmap[i + 1][j + 1].b + img->bitmap[i - 1][j - 1].b + img->bitmap[i + 1][j - 1].b + img->bitmap[i - 1][j + 1].b)/8;

			} else if(i == 0 && j == 0)
			{
				r = (img->bitmap[i + 1][j].r + img->bitmap[i + 1][j + 1].r + img->bitmap[i][j + 1].r)/3;
				g = (img->bitmap[i + 1][j].g + img->bitmap[i + 1][j + 1].g + img->bitmap[i][j + 1].g)/3;
				bl = (img->bitmap[i + 1][j].b + img->bitmap[i + 1][j + 1].b + img->bitmap[i][j + 1].b)/3;

			} else if(i == img->height - 1 && j == 0)
			{
				r = (img->bitmap[i - 1][j].r + img->bitmap[i - 1][j + 1].r + img->bitmap[i][j + 1].r)/3;
				g = (img->bitmap[i - 1][j].g + img->bitmap[i - 1][j + 1].g + img->bitmap[i][j + 1].g)/3;
				bl = (img->bitmap[i - 1][j].b + img->bitmap[i - 1][j + 1].b + img->bitmap[i][j + 1].b)/3;

			} else if(i == 0 && j == img->width - 1)
			{
				r = (img->bitmap[i][j - 1].r + img->bitmap[i + 1][j - 1].r + img->bitmap[i + 1][j].r)/3;
				g = (img->bitmap[i][j - 1].g + img->bitmap[i + 1][j - 1].g + img->bitmap[i + 1][j].g)/3;
				bl = (img->bitmap[i][j - 1].b + img->bitmap[i + 1][j - 1].b + img->bitmap[i + 1][j].b)/3;

			} else if(i == img->height - 1 && j == img->width - 1)
			{
				r = (img->bitmap[i][j - 1].r + img->bitmap[i - 1][j - 1].r + img->bitmap[i][j - 1].r)/3;
				g = (img->bitmap[i][j - 1].g + img->bitmap[i - 1][j - 1].g + img->bitmap[i][j - 1].g)/3;
				bl = (img->bitmap[i][j - 1].b + img->bitmap[i - 1][j - 1].b + img->bitmap[i][j - 1].b)/3;

			} else if(i != 0 && j == 0)
			{
				r = (img->bitmap[i + 1][j].r + img->bitmap[i + 1][j + 1].r + img->bitmap[i][j + 1].r + img->bitmap[i - 1][j + 1].r + img->bitmap[i - 1][j].r)/5;
				g = (img->bitmap[i + 1][j].g + img->bitmap[i + 1][j + 1].g + img->bitmap[i][j + 1].g + img->bitmap[i - 1][j + 1].g + img->bitmap[i - 1][j].g)/5;
				bl = (img->bitmap[i + 1][j].b + img->bitmap[i + 1][j + 1].b + img->bitmap[i][j + 1].b + img->bitmap[i - 1][j + 1].b + img->bitmap[i - 1][j].b)/5;

			} else if(i != 0 && j == img->width - 1)
			{
				r = (img->bitmap[i + 1][j].r + img->bitmap[i + 1][j - 1].r + img->bitmap[i - 1][j].r + img->bitmap[i][j - 1].r + img->bitmap[i - 1][j - 1].r)/5;
				g = (img->bitmap[i + 1][j].g + img->bitmap[i + 1][j - 1].g + img->bitmap[i - 1][j].g + img->bitmap[i][j - 1].g + img->bitmap[i - 1][j - 1].g)/5;
				bl = (img->bitmap[i + 1][j].b + img->bitmap[i + 1][j - 1].b + img->bitmap[i - 1][j].b + img->bitmap[i][j - 1].b + img->bitmap[i - 1][j - 1].b)/5;
			
			} else if(i == 0 && j != 0)
			{
				r = (img->bitmap[i + 1][j].r + img->bitmap[i + 1][j - 1].r + img->bitmap[i][j + 1].r + img->bitmap[i][j - 1].r + img->bitmap[i + 1][j + 1].r)/5;
				g = (img->bitmap[i + 1][j].g + img->bitmap[i + 1][j - 1].g + img->bitmap[i][j + 1].g + img->bitmap[i][j - 1].g + img->bitmap[i + 1][j + 1].g)/5;
				bl = (img->bitmap[i + 1][j].b + img->bitmap[i + 1][j - 1].b + img->bitmap[i][j + 1].b + img->bitmap[i][j - 1].b + img->bitmap[i + 1][j + 1].b)/5;
			
			} else if(i == img->height - 1 && j != 0)
			{
				r = (img->bitmap[i - 1][j].r + img->bitmap[i][j - 1].r + img->bitmap[i][j + 1].r + img->bitmap[i - 1][j - 1].r + img->bitmap[i - 1][j + 1].r)/5;
				g = (img->bitmap[i - 1][j].g + img->bitmap[i][j - 1].g + img->bitmap[i][j + 1].g + img->bitmap[i - 1][j - 1].g + img->bitmap[i - 1][j + 1].g)/5;
				bl = (img->bitmap[i - 1][j].b + img->bitmap[i][j - 1].b + img->bitmap[i][j + 1].b + img->bitmap[i - 1][j - 1].b + img->bitmap[i - 1][j + 1].b)/5;
			}
			
			
			pixel n;

			n.r = r;
			n.g = g;
			n.b = bl;

			setPixelT(i,j,n,img);
		}
	}	

	pthread_exit(NULL);

}


void* zoomT(void* data){

	struct data* my_data;
	my_data = (struct data *) data;
	cout << "Applying zoomT filter con..." << (int) my_data->n_threads <<  endl; // cuando tenemos punteros a struct, sus miembros se refieren con -> en vez de .

	//Calculo de limites
	ppm *img = my_data->img1;
	ppm *img2 = my_data->img2;
	ppm *img3 = my_data->imgM;

	int newSize = img2->height / img->height;
	int cont1 = 0;
	int cont2 = 0;

	int interval = img->width/my_data->n_threads;

	int start = 0;

	if (my_data->tid == 0)
	{
		start = 0;
	}else
	{
		start = interval * my_data->tid;
	}
	
	int end = start + interval;

	for(int i=start;i<interval;i++){
		cont2 = 0;
		for(int j=0;j<img->width;j++){
			int r = img->bitmap[i][j].r;
			int g = img->bitmap[i][j].g;
			int bl = img->bitmap[i][j].b;
			pixel n;

			n.r = r;
			n.g = g;
			n.b = bl;
			
			setPixelT(cont1,cont2,n,img2);

			if (newSize == 2){
				setPixelT(cont1,cont2+1,n,img2);
				setPixelT(cont1+1,cont2,n,img2);
				setPixelT(cont1+1,cont2+1,n,img2);	
			}/* else if(newSize == 3){
				setPixelT(cont1,cont2+1,n,img2);
				setPixelT(cont1+1,cont2,n,img2);
				setPixelT(cont1+1,cont2+1,n,img2);
				setPixelT(cont1,cont2+2,n,img2);
				setPixelT(cont1+2,cont2,n,img2);
				setPixelT(cont1+2,cont2+1,n,img2);
				setPixelT(cont1+1,cont2+2,n,img2);
				setPixelT(cont1+2,cont2+2,n,img2);
			}	 */
			
			cont2 = cont2 + newSize;
		}
		cont1 = cont1 + newSize;
	}

	pthread_exit(NULL);

}
