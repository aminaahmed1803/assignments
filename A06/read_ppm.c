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
  char x = fgetc(infile);
  if (x!='P')
  {
    printf("Invalid file");
    exit(1);
  }
  x = fgetc(infile);
  if (x!='6')
  {
    printf("Invalid file");
    exit(1);
  }
  x = fgetc(infile);
  x = fgetc(infile);
  if (x == '#'){
    while( getc(infile) != '\n');
    fscanf(infile, "%d %d %d", w, h, &maxVal);
  }
  else {
    int co = 10;
    *w = atoi(&x);
    while (x != ' ')
    {
      x = getc(infile);
      int v = atoi(&x); 
      *w = (v *co) + *w;
      co = co*10; 
    }
    fscanf(infile, " %d %d",  h, &maxVal);
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

  fclose(infile);
  return matrix;
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel** pxs, int w, int h) {

    FILE* outfile = NULL;

    printf("Writing file %s",filename);
    outfile = fopen(filename, "w");
    if (outfile == NULL) {
        printf("Error: unable to open outfile\n");
        exit(1);
    }

    putc('P',outfile);
    putc('6',outfile);
    putc('\n',outfile);
    putw(w,outfile);
    putc(' ',outfile);
    putw(h,outfile);
    putc('\n',outfile);
    putc('2',outfile);
    putc('2',outfile);
    putc('5',outfile);

    for (int i=0 ; i<h ; i++){
      for (int j=0 ; j<w ; j++){
        fwrite(&pxs[i][j],sizeof(struct ppm_pixel), 1,outfile);
      }
    }

    fclose(outfile);
}