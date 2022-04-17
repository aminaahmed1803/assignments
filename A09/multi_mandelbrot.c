#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"

void generate_set(struct ppm_pixel* color, int size, int xmin, int xmax, int ymin, int ymax, int maxIterations, struct ppm_pixel* palette, int process)
{
  int i_start= 0, i_end = size;
  int j_start= 0, j_end = size;

  if (process == 0)
  {
    i_start= 0, 
    i_end = size/2;
    j_start= 0;
    j_end = size/2;
      
  }
  else if (process == 1)
  {
    i_start= size/2, 
    i_end = size;
    j_start= 0;
    j_end = size/2;
  }
  else if (process == 2)
  {
    i_start= 0, 
    i_end = size/2;
    j_start= size/2;
    j_end = size;
      
  }
  else if (process == 3)
  {
    i_start= size/2, 
    i_end = size;
    j_start= size/2;
    j_end = size;
  }

  for (int i= i_start ; i<i_end ; i++) { //each row in the image
    for (int j=j_start ; j<j_end ; j++) {//each col in the image
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
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;
  struct ppm_pixel palette[1000];
  int f= size/numProcesses;

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

  // generate palle
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

  /*struct ppm_pixel **color = (struct ppm_pixel**)malloc(size * sizeof(struct ppm_pixel*));
    for (int i = 0; i < size ; i++)
      color[i] = (struct ppm_pixel*) malloc( size * sizeof(struct ppm_pixel) );
*/
  int shmid; 
  shmid = shmget(IPC_PRIVATE, sizeof(struct ppm_pixel) * size * size , 0644 | IPC_CREAT);
  if (shmid == -1) {
    perror("Error: cannot initialize shared memory\n");
    exit(1);
  }
  
  struct ppm_pixel* color = shmat(shmid, NULL, 0);
  if (color == (void*) -1) {
    perror("Error: cannot access shared memory\n");
    exit(1);
  } 

  
  //buffer[40] = '\0';
  clock_t t = clock();
  for (int i = 0; i < numProcesses ; i++) {
    int pid = fork();
    if (pid == 0) {
      //char c = i+'1'; // convert from integer to char
      //for (int j = 0; j < 9; j++) {
      //  buffer[i*10 + j] = c;
      //}
      generate_set(color, size, xmin, xmax, ymin, ymax, maxIterations, palette, i);
      //buffer[i*10+9] = '\n';
      exit(0);
    } else {
      printf("Launched child process: %d\n", pid);
    }
  }

  for (int i = 0; i <  numProcesses ; i++) {
    int status;
    int pid = wait(&status);
    printf("Child process complete: %d\n", pid);
  }

  // compute image
  //clock_t t = clock();
  //generate_set(color, size, xmin, xmax, ymin, ymax, maxIterations, palette);
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

  //free colour
  //free(color);

   if (shmdt(color) == -1) {
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }

  if (shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("Error: cannot remove shared memory\n");
    exit(1);
  }   
}
