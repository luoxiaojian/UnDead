
#include "Kakuzu.h"

Image::Image(int w, int h, int c, int p) {
	width=w;
	height=h;
	channel=c;
	padding=p;

	width_t=w+p*2;
	height_t=h+p*2;

	size=width_t*height_t*channel;
	data=(float*)malloc(sizeof(float)*size);
	generateRandomImage();
}

void Image::generateRandomImage() {
	memset(data, 0, size*sizeof(float));
	for(int ic=0; ic<channel; ic++) {
		int offset=ic*width_t*height_t;
		for(int i=0; i<height; i++) {
			for(int j=0; j<width; j++) {
				data[offset+(i+padding)*width_t+(j+padding)]=((float)rand())/((float)RAND_MAX);
			}
		}
	}
}

void Image::output(FILE* fout) {
	for(int ic=0; ic<channel; ic++) {
		int offset=ic*width_t*height_t;
		for(int i=0; i<height; i++) {
			for(int j=0; j<width; j++) {
				fprintf(fout, "%.7f ", data[offset+(i+padding)*width_t+(j+padding)]);	
			}
			fprintf(fout, "\n");
		}
	}
}

Filter::Filter(int w, int h, int c) {
	width=w;
	height=h;
	channel=c;
	size=w*h*c;
	data=(float*)malloc(sizeof(float)*size);
	generateRandomFilter();
}

void Filter::output(FILE *fout) {
	for(int ic=0; ic<channel; ic++) {
		int offset=ic*width*height;
		for(int i=0; i<height; i++) {
			for(int j=0; j<width; j++) {
				fprintf(fout, "%.7f ", data[offset+i*width+j]);
			}
			fprintf(fout, "\n");
		}
	}
}

void Filter::generateRandomFilter() {
	for(int i=0; i<size; i++) {
		data[i]=((float)rand())/((float)RAND_MAX);
	}
}

void Kakuzu::run() {
	for(int iFilter=0; iFilter<filter_num; iFilter++) {
		float *icur=&(image_out.data[iFilter*image_out.width_t*image_out.height_t]);
		for(int i=0; i<image_out.height; i++)
			for(int j=0; j<image_out.width; j++) {
				icur[(i+image_out.padding)*image_out.width_t+j+image_out.padding]=0.0f;
				for(int iChannel=0; iChannel<channel; iChannel++)
					icur[(i+image_out.padding)*image_out.width_t+j+image_out.padding]+=conv(j, i, iFilter, iChannel);
			}
	}	
}

float Kakuzu::conv(int x, int y, int fid, int cid) {
	float acc=0.0f;
	float *fcur=&(filters[fid].data[cid*width_f*height_f]);
	float *icur=&(image_in.data[cid*image_in.height_t*image_in.width_t]);
	for(int a=0; a<height_f; a++)
		for(int b=0; b<width_f; b++)
			acc+=fcur[(height_f-a-1)*width_f+width_f-b-1]*icur[(a+y)*image_in.width_t+b+x];
	return acc;
}
