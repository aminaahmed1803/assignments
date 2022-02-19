/***************************************************
 * ascii_image.c
 * Author: Amina Ahmed
 * Date: 2/18/2022
 * Prints Ascii art after reading files
 */
#include <stdio.h>
#include <string.h>
#include "read_ppm.c"
#include <stdlib.h>

int main(int argc, char** argv) {  //

  //get filename
  if (argc != 2)
  {
    printf("Usage: ./asscii_image \n");
    exit(0);
  }
  char filename[32];
  strncpy(filename, argv[1], 32);
  
  int w, h;
  struct ppm_pixel **matrix = read_ppm(filename, &w, &h);
  if (matrix == NULL)
  {
    printf("Error\n");
    exit(1);
  }

  //convert from rbg to characters
  char ascii[h][w]; 
  int Intsity; 
  for (int i = 0; i <h; i++){
    for (int j = 0; j < w; j++){
      Intsity = (matrix[i][j].red+ matrix[i][j].blue+matrix[i][j].green) / 3;
      if (Intsity < 26) ascii[i][j] = '@';
      else if ( Intsity < 51 ) ascii[i][j] = '#';
      else if (Intsity < 76 ) ascii[i][j] = '%';
      else if (Intsity < 101 ) ascii[i][j] = '*';
      else if ( Intsity < 126 ) ascii[i][j] = 'o';
      else if ( Intsity < 151 ) ascii[i][j] = ';';
      else if (Intsity < 176 ) ascii[i][j] = ':';
      else if (Intsity < 201 ) ascii[i][j] = ',';
      else if ( Intsity < 226 ) ascii[i][j] = '.';
      else ascii[i][j] = ' ';
    }
  } 

  //printing
  printf("Reading file %s with width %d and height %d\n", filename, w, h);
  for (int i = 0; i < h; i++){
    for (int j = 0; j <w; j++){
      printf("%c", ascii[i][j]);
    }
    printf("\n");
  } 

  //free memory allocated
  for (int i = 0; i <w; i++){
    free(matrix[i]); 
  }
  free(matrix);
  matrix = NULL;
  return 0;
  
  return 0;
}
