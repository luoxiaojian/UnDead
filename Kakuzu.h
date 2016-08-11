#ifndef _KAKUZU_H_
#define _KAKUZU_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <time.h>

using std::vector;

class Image {
	public:
		explicit Image(int w, int h, int c, int p);
		void output(FILE* fout);

		int width, height;
		int channel;
		int padding;

		int width_t, height_t;
		int size;

		float *data;

		void generateRandomImage();
};

class Filter {
	public:
		explicit Filter(int w, int h, int c);
		void output(FILE* fout);

		int width, height;
		int channel;

		int size;

		float *data;

		void generateRandomFilter();
};

class Kakuzu {
	public:
		explicit Kakuzu(int iw, int ih, int fw, int fh, int fn, int cn)
			: width_i(iw),
			  height_i(ih),
			  width_o(iw),
			  height_o(ih),
			  width_f(fw),
			  height_f(fh),
			  filter_num(fn),
			  channel(cn),
			  image_in(iw, ih, cn, fw/2),
			  image_out(iw, ih, fn, 0) {
				  srand((unsigned)time(NULL));
				  for(int i=0; i<fn; i++)
					  filters.push_back(Filter(fw, fh, cn));
			  }

		void run();

		Image image_in, image_out;
		vector<Filter> filters;

		int width_i, height_i;
		int width_o, height_o;
		int width_f, height_f;
		int channel, filter_num;

		float conv(int x, int y, int fid, int cid);
};

#endif
