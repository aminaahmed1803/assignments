#include <stdio.h>
#include "read_ppm.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {  
  //get file 

  char filename[32]; 
  int w, h;
  
  if (argc != 2)
  {
    printf("Usage: ./test_ppm \n");
    exit(0);
  }
  strncpy(filename, argv[1], 32);
  

  struct ppm_pixel **matrix = read_ppm(filename, &w, &h);
  if (matrix == NULL)
  {
    printf("Error\n");
    exit(1);
  }
  
  printf("Testing file %s: %d %d\n", filename, w, h);
  for (int i = 0; i <w; i++){
    for (int j = 0; j < h; j++){
      printf("(%d,%d,%d) ", matrix[i][j].red, matrix[i][j].blue, matrix[i][j].green); ///
    }
    printf("\n"); 
  } 
  
  for (int i = 0; i <w; i++){
    free(matrix[i]); 
  }
  free(matrix);
  matrix = NULL;
  return 0;
}


