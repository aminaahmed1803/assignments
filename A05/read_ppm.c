#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel** read_ppm(const char* filename, int* w, int* h) {

  //OPEN FILE
  FILE* infile = NULL;
  int maxVal;

  infile = fopen(filename, "rb");
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    exit(1);
  }

  //identify file
  char line[32];
  char x;  
  fgets(line, sizeof(line),infile);
  x = fgetc(infile);
  if (x != '#'){
    *w = atoi(&x);
    fscanf(infile, " %d %d ",h, &maxVal);
  }
  else 
  {
    while( getc(infile) != '\n');
    fscanf(infile, "%d %d %d", w, h, &maxVal);
  }

  //declare td Array
  struct ppm_pixel **matrix = (struct ppm_pixel**)malloc(*h * sizeof(struct ppm_pixel*));
  for (int i = 0; i < *h ; i++)
    matrix[i] = (struct ppm_pixel*) malloc( *w * sizeof(struct ppm_pixel) );

  //code to exit if space not allocated == CHECK
  if (matrix == NULL )
  {
    printf("Cannot allocate space..\n");
    return NULL;
  }
  for (int i = 0 ; i < *w ; i++)
  {
    if (matrix[i] == NULL )
    {
      printf("Cannot allocate space \n");
      return NULL;
    }
  }

  //reaadfile
  for (int i=0 ; i<*h ; i++){
    for (int j=0 ; j<*w ; j++){
      fread(&matrix[i][j],sizeof(struct ppm_pixel), 1,infile);
    }
  }

  return matrix;
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel** pxs, int w, int h) {

}

int main() {  

  int w, h; 
  struct ppm_pixel **matrix = read_ppm("monalisa.ppm", &w, &h);
  if (matrix == NULL)
  {
    printf("Error\n");
    exit(1);
  }
  
  printf("Testing file %s: %d %d\n", "monalisa.ppm", w, h);
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
