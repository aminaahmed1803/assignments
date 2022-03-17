#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {

  char filename[32]; 
  int w, h;
  
  if (argc != 2)
  {
    printf("Usage: ./test_ppm \n");
    exit(1);
  }
  strncpy(filename, argv[1], 32);

  struct ppm_pixel **matrix = read_ppm(filename, &w, &h);
  if (matrix == NULL)
  {
    printf("Error\n");
    exit(1);
  }

  srand(time(0));
  for (int i = 0; i <h; i++){
    for (int j = 0; j < w; j++){
      matrix[i][j].red = matrix[i][j].red << (rand() % 2); 
      matrix[i][j].green = matrix[i][j].green << (rand() % 2);
      matrix[i][j].blue = matrix[i][j].blue << (rand() % 2);
    } 
  } 
  
  write_ppm(filename,matrix,w,h);

  for (int i = 0; i <w; i++){
    free(matrix[i]); 
  }
  free(matrix);
  matrix = NULL;
  return 0;
}
