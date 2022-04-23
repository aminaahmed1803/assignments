#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {

  // your code here
  return NULL;
}

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
  
    // your code here
    FILE* outfile = NULL;

    printf("Writing file %s\n",filename);
    outfile = fopen(filename, "w");
    if (outfile == NULL) {
        printf("Error: unable to open outfile\n");
        exit(1);
    }

    fprintf(outfile, "P6\n%d %d\n225\n", w, h);


    for (int i=0 ; i<h ; i++){
      for (int j=0 ; j<w ; j++){
        int idx=(i*h)+j;
        fwrite(&pixels[idx]  , sizeof(struct ppm_pixel), 1,outfile);
      }
    }

    fclose(outfile);
}

