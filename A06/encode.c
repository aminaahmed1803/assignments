#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {

  char filename[32]; 
  int w, h, max,  max_bits;
  char * message = NULL; 
  int * bits = NULL;
  int idx =0;
  
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

  max_bits = w*h*3 ;
  max = max_bits / 8;

  message = (char*) malloc(max* sizeof(char));
  //for (int j = 0; j < max; j++)
  //  message[j] = '\0';
  printf("Reading %s with width %d and height %d\n", filename, w, h);
  printf("Max number of characters in the image: %d\n", max);
  printf("Enter a phrase: ");
  fgets(message, max, stdin);

  bits = (int*) malloc(max_bits* sizeof(int));
  for (int i = 0; message[i] != '\0'; i++)
  { 
    int ascii = message[i];
    for (int i=idx+7; i>idx ; i--)
    {
      if (ascii <= 0)
        bits[i] =0;
      else 
      {
        bits[i] = ascii %2;
        ascii= ascii/2; 
      }
    }
    idx = idx+8;
  }

  for (int i = 0; i<max_bits; i++)
    printf("%d",bits[i]);

  idx = 0;

  for (int i = 0; i <w; i++){
    for (int j = 0; j < h; j++){

      //red
      if (matrix[i][j].red%2 == 0 && bits[idx] == 1 )
        matrix[i][j].red++; 
      else if (matrix[i][j].red%2 == 1 && bits[idx] == 0 )
        matrix[i][j].red++; 
      idx++;

      //green
      if (matrix[i][j].green%2 == 0 && bits[idx] == 1 )
        matrix[i][j].green++; 
      else if (matrix[i][j].green%2 == 1 && bits[idx] == 0 )
        matrix[i][j].green++; 
      idx++; 

      //blue
      if (matrix[i][j].blue%2 == 0 && bits[idx] == 1 )
        matrix[i][j].blue++; 
      else if (matrix[i][j].blue%2 == 1 && bits[idx] == 0 )
        matrix[i][j].blue++;
      idx++; 
    }
  }

  
  write_ppm(filename, matrix, w, h);

  free(message);
  message = NULL;

  free(bits);
  bits = NULL;

  for (int i = 0; i <w; i++){
    free(matrix[i]); 
  }
  free(matrix);
  matrix = NULL;
  

  return 0;
}

