/***************************************************
 * ascii_image.c
 * Author: Amina Ahmed
 * Date: 2/18/2022
 * Reads file and stores in array
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"


struct ppm_pixel** read_ppm(const char* filename, int* w, int* h) {

  //OPEN FILE
  FILE* infile = NULL;
  int maxVal=0;

  infile = fopen(filename, "r");
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    exit(1);
  }

  //identify file
  char line[32]= " ";
  char x=' ';  
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
  for (int i = 0 ; i < *h ; i++)
  {
    if (matrix[i] == NULL )
    {
      printf("Cannot allocate space \n");
      return NULL;
    }
  }
    //read and store values
  int r =0, b=0, g=0;  
  for (int i=0 ; i<*h ; i++){
        for (int j=0 ; j<*w ; j++){

          fscanf(infile, " %d %d %d", &r, &g, &b);
          if ( (r == EOF) | (g == EOF) | (b==EOF)) break;
          matrix[i][j].red = r; 
          matrix[i][j].green = g;
          matrix[i][j].blue = b;
       }
    }
  return matrix;
}
