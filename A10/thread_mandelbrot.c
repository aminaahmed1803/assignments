#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"


struct threadData {
	struct ppm_pixel* color;
	struct ppm_pixel* palette;
	int size;
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	int maxIterations;
	int i_begin;
	int i_end;
	int j_begin;
  int j_end;
};


void generate_set(struct threadData* data)
{

  printf("Thread sub-image block: cols (%d, %d) to rows (%d, %d)\n", data->j_begin, data->j_end, data->i_begin, data->i_end);

  struct ppm_pixel* color = data->color; 
  struct ppm_pixel* palette = data->palette;
  int size = data->size;
  int xmin = data->xmin; 
  int xmax = data->xmax;
  int ymin = data->ymin;
  int ymax = data->ymax; 
  int maxIterations = data->maxIterations ;
  int i_begin = data->i_begin;
  int i_end = data->i_end;
  int j_begin = data->j_begin;
  int j_end = data->j_end;

  for (int i= i_begin ; i<i_end ; i++) { //each row in the image
    for (int j=j_begin ; j<j_end ; j++) {//each col in the image
      
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

      int idx = (i*size) + j;
      if (iter < maxIterations) 
      {
        color[idx].red = palette[iter].red;
        color[idx].green = palette[iter].green;
        color[idx].blue = palette[iter].blue;
      }
      else
      {
        color[idx].red = 0;
        color[idx].green = 0;
        color[idx].blue = 0;
      }   
   }
  }
  printf("Thread finished\n");
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  struct ppm_pixel palette[1000];
  int numProcesses = 4;
  int i_begin;
	int i_end;
	int j_begin;
  int j_end;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your code here
  
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
  
  // compute image
  clock_t t = clock();

  struct ppm_pixel *color = (struct ppm_pixel*)malloc(size * size * sizeof(struct ppm_pixel*)); 
  	if (color == NULL) {
		printf("Malloc failed");
		return -1;
	}

  //generate_set( color, palette, size, xmin, xmax, ymin,ymax, maxIterations, 0, size, 0, size);

  pthread_t one;
	pthread_t two;
	pthread_t three;
	pthread_t four;

  struct threadData td_one = {color, palette, size, xmin, xmax, ymin, ymax, maxIterations, 0, size/2, 0, size/2};
  struct threadData td_two = {color, palette, size, xmin, xmax, ymin, ymax, maxIterations, 0, size/2, size/2, size};
  struct threadData td_three = {color, palette, size, xmin, xmax, ymin, ymax, maxIterations, size/2, size, 0, size/2};
  struct threadData td_four = {color, palette, size, xmin, xmax, ymin, ymax, maxIterations, size/2, size, size/2, size};

  pthread_create(&one, NULL, (void*) generate_set, (void*) &td_one);
  pthread_create(&two, NULL, (void*) generate_set, (void*) &td_two);
  pthread_create(&three, NULL, (void*) generate_set, (void*) &td_three);
  pthread_create(&four, NULL, (void*) generate_set, (void*) &td_four);

  pthread_join(one, NULL);
	pthread_join(two, NULL);
	pthread_join(three, NULL);
	pthread_join(four, NULL);

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
  strncat(filename, s, 99 );
  strncat(filename, "-", 99 );
  strncat(filename, ti, 99 );
  strncat(filename, ".ppm", 99 );

  write_ppm(filename,color,size,size);

  free(color);

}
