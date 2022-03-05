#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"

int toDec (int n, int i )
  {
    if (n >=1)
    {
      return (n%10)*i + toDec(n/10, i*2);
    }
    return 0; 
  }   

int * get_numbers (struct ppm_pixel** pxs, int w, int h){

  int bits = w*h*3, idx = 0, chars = bits/8;
  printf("Max number of characters in the image: %d\n", chars);
  
  int * b = (int *)malloc(bits*sizeof(int));

  for (int i=0; i<w ; i++){
    for(int j=0; j<h; j++){
      //if (i ==0 && j==0 ) continue;
      b[idx] = pxs[i][j].red % 2;
      idx++;
      b[idx] = pxs[i][j].green % 2;
      idx++;
      b[idx] = pxs[i][j].blue % 2;
      idx++;
    }
  } 
  /*for (int i=0; i<bits ; i++){
    printf("%d", b[i]);
    i++;
    printf("%d", b[i]);
    i++;
    printf("%d", b[i]);
    i++;
    printf("%d", b[i]);
    i++;
    printf("%d", b[i]);
    i++;
    printf("%d", b[i]);
    i++;
    printf("%d", b[i]);
    i++;
    printf("%d\n", b[i]);
    
  }*/
  idx =0;
  int * c = (int *)malloc(chars*sizeof(int));
  for (int i = 0; i < bits; idx++)
  { 
    int count=0, coeff = 10000000, temp = 0;  
    while (count <8 )
    { 
      temp += b[i]*coeff;
      i++; 
      coeff = coeff/10;
      count++; 
    }
    c[idx] = temp;
  }
  free(b);
  return c; 
}


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

  int bits = w*h*3, chars = bits/8;
  printf("Reading tiny_encoded.ppm with width %d and height %d\n", w, h);
  int * c = get_numbers(matrix,w,h);
  printf("\n");
  for (int i = 0; i<chars-1 ; i++)
  {
    printf("%c", toDec(c[i],1) );
  }


  free (c);
  for (int i = 0; i <w; i++){
    free(matrix[i]); 
  }
  free(matrix);
  matrix = NULL;
  return 0;
}

