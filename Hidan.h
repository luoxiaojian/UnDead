#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>

using std::vector;

class Image {
    public:
        explicit Image(int w, int h, int c);
        void output(FILE* fout);

        int width, height, channel;
        float *data;
        int size;

        void generateRandomImage();
};

class Filter {
    public:
        explicit Filter(int w, int h, int c);
        void output(FILE* fout);

        int width, height, channel;
        float* data;
        int size;

        void generateRandomFilter();
};

class Hidan {
    public:
        explicit Hidan(int iw, int ih, int fw, int fh, int fn, int cn)
            : width_i(iw),
              height_i(ih),
              width_o(iw-fw+1),
              height_o(ih-fh+1),
              width_f(fw),
              height_f(fh),
              filter_num(fn),
              channel(cn),
              image_in(iw, ih, cn),
              image_out(iw-fw+1, ih-fh+1, fn) {
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
