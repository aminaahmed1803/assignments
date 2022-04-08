#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include "read_ppm.h"

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  struct ppm_pixel palette[1000];
  
  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your work here

  // generate pallet
  srand(time(0));
  int basered = rand() % 255;
  int basegreen = rand() % 255;
  int baseblue = rand() % 255;
  for (int i = 0; i < 1000; i++)
  {
    palette[i].red = basered + rand() % 100 - 50;
    palette[i].green = basegreen + rand() % 100 - 50;
    palette[i].blue = baseblue + rand() % 100 - 50;
  }

  //pallet("pal.ppm", palette, 1000);
   // compute imge
  struct ppm_pixel **color = (struct ppm_pixel**)malloc(size * sizeof(struct ppm_pixel*));
    for (int i = 0; i < size ; i++)
      color[i] = (struct ppm_pixel*) malloc( size * sizeof(struct ppm_pixel) );
 

 clock_t t = clock();
  for (int i=0 ; i<size ; i++) { //each row in the image
    for (int j=0 ; j<size ; j++) {//each col in the image
      float xfrac = ((float)j)/size;
      float yfrac = ((float)i)/size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);

      float x = 0, y = 0;
      int iter = 0;
      while (iter < maxIterations && x*x + y*y < 2*2){
        float xtmp = (x*x) - (y*y) + x0;
        y = (2*x*y) + y0;
        x = xtmp;
        iter++;
      }
      //printf("%d ", iter);
      if (iter < maxIterations) 
      {
        color[i][j].red = palette[iter].red;
        color[i][j].green = palette[iter].green;
        color[i][j].blue = palette[iter].blue;
      }
      else
      {
        color[i][j].red = 0;
        color[i][j].green = 0;
        color[i][j].blue = 0;
      }   
   }
  }
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC;
  printf("Computed mandelbrot set (%dx%d) in %f seconds\n", size, size, time_taken );

  //write filename
  char ti[20]; 
  char s[10]; 
  time_t now = time(0);
  snprintf( s, 10, "%d", size );
  snprintf( ti, 20, "%ld", now  );

  char filename[100] = "mandelbrot-";
  strncat(filename, s, 100 );
  strncat(filename, "-", 100 );
  strncat(filename, ti, 100 );
  strncat(filename, ".ppm", 100 );

  write_ppm(filename,color,size,size);


  for (int i = 0; i < size ; i++)
    free(color[i]);
  free(color);
}
