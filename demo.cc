#include "Hidan.h"
#include <stdio.h>

int main() {
    FILE *fout=fopen("result.dat", "w+"); 
    Hidan hd(5, 5, 3, 3, 2, 2);
    hd.run();
    fprintf(fout, "input image:\n");
    hd.image_in.output(fout);
	for(int i=0; i<hd.filters.size(); i++) {
		fprintf(fout, "filter%d:\n", i);
		hd.filters[i].output(fout);
	}
    fprintf(fout, "result:\n");
    hd.image_out.output(fout);
    fflush(fout);
    fclose(fout);
    return 0;
}
