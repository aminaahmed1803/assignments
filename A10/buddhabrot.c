#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"

struct threadData {
  bool* belongs; 
  int* counts;
	struct ppm_pixel* color;
  pthread_mutex_t* mutex;
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

void generate_set (struct threadData* data ){

  printf("Thread sub-image block: cols (%d, %d) to rows (%d, %d)\n", data->j_begin, data->j_end, data->i_begin, data->i_end);

  bool* belongs = data->belongs; 
  int* counts = data->counts;
	struct ppm_pixel* color = data->color;
  pthread_mutex_t * mutex = data->mutex;
	int size = data->size;
	float xmin = data->xmin;
	float xmax= data->xmax;
	float ymin = data->ymin;
	float ymax = data->ymax;
	int maxIterations = data->maxIterations;
	int i_begin = data->i_begin;
	int i_end = data->i_end;
	int j_begin = data->j_begin;
  int j_end = data->j_end;

  //STEP 1
  for(int i = i_begin ; i< i_end ; i++){ //for each row in the image
   for (int j = j_begin; j< j_end ; j++){//for each column in the image
      float xfrac = ((float)j)/size;
      float yfrac = ((float)i)/size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);

      float x = 0.0;
      float y = 0.0;
      int iter = 0;
      while (iter < maxIterations && x*x + y*y < 2*2){
        float xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
      }

      int idx = (i*size) + j;
      if (iter < maxIterations){ // escaped
        belongs[idx] = false; // set membership at (row,col) to false
      }
      else {
        belongs[idx] = true;  //set membership at (row,col) to true
      }
    }
  }

  //STEP 2
  long max_count = 0; 
  for(int i = i_begin ; i< i_end ; i++){ //for each row in the image
   for (int j = j_begin; j< j_end ; j++){//for each column in the image
      if (belongs[i*size+j]) {
        continue;
      } else {
        float xfrac = (float) j / size;
        float yfrac = (float) i / size;
        float x0 = xmin + xfrac * (xmax - xmin);
        float y0 = ymin + yfrac * (ymax - ymin);

        float x = 0;
        float y = 0;
        while (x*x + y*y < 2*2) {
          float xtmp = x*x - y*y + x0;
          y = 2*x*y + y0;
          x = xtmp;

          float yrow = round(size * (y - ymin) / (ymax - ymin));
          float xcol = round(size * (x - xmin) / (xmax - xmin));

          if (yrow < 0 || yrow >= size) continue; // out of range
          if (xcol < 0 || xcol >= size) continue; // out of range
          
          
	        pthread_mutex_lock(mutex);
          int idx = yrow*size + xcol;
          counts[idx]++;

          // update max count
          if (counts[idx] > max_count) 
            max_count = counts[idx];
          pthread_mutex_unlock(mutex);
	      }
      }
    }
  }
  pthread_barrier_t barrier;
  int ret1 = pthread_barrier_init(&barrier, NULL, 4);
  if (ret1) {
    printf("ERROR: pthread_barrier_init failed\n");
    exit(0);
  }
  pthread_barrier_wait(&barrier);

  //generate color 
  float gamma = 0.681;
  float factor = 1.0/gamma;
  for(int i = i_begin ; i< i_end ; i++){ //for each row in the image
   for (int j = j_begin; j< j_end ; j++){//for each column in the image
      
      int idx = (i*size) + j;
      float value = 0; 

      if (counts[idx] > 0){ //counts at (row,col) are greater than zero
        value = log((float)counts[idx]) / log(max_count);
        value = pow(value, factor);
      }
      //write color to image at location (row,col)
      color[idx].red = value * 255;
      color[idx].green = value * 255;
      color[idx].blue = value * 255;
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
  int numProcesses = 4;

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
   clock_t t = clock();

  //allocate memory
  struct ppm_pixel *color = (struct ppm_pixel*)malloc(size * size * sizeof(struct ppm_pixel*)); 
  bool * belongs = (bool*)malloc(size * size * sizeof(bool*));
  int * counts = (int*)calloc(size*size, sizeof(int));

  //generate_set(belongs, counts, color, size, xmin, xmax, ymin, ymax, maxIterations );
  pthread_t one;
	pthread_t two;
	pthread_t three;
	pthread_t four;

  pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

  struct threadData td_one   = {belongs, counts, color, &mutex, size, xmin, xmax, ymin, ymax, maxIterations, 0, size/2, 0, size/2};
  struct threadData td_two   = {belongs, counts, color, &mutex, size, xmin, xmax, ymin, ymax, maxIterations, 0, size/2, size/2, size};
  struct threadData td_three = {belongs, counts, color, &mutex, size, xmin, xmax, ymin, ymax, maxIterations, size/2, size, 0, size/2};
  struct threadData td_four  = {belongs, counts, color, &mutex, size, xmin, xmax, ymin, ymax, maxIterations, size/2, size, size/2, size};

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
  printf("Computed buddhabrot set (%dx%d) in %f seconds\n", size, size, time_taken );


  //write file
  char ti[20]; 
  char s[10]; 
  time_t now = time(0);
  snprintf( s, 10, "%d", size );
  snprintf( ti, 20, "%ld", now  );
  char filename[100] = "buddhabrot-";
  strncat(filename, s, 99 );
  strncat(filename, "-", 99 );
  strncat(filename, ti, 99 );
  strncat(filename, ".ppm", 99 );

  write_ppm(filename,color,size,size);

  //free memory
  free(color);
  color = NULL;

  free(belongs);
  belongs = NULL;

  free(counts);
  counts = NULL;
}
