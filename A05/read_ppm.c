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

  fclose(infile);
  return matrix;
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel** pxs, int w, int h) {

    FILE* infile = NULL;
    FILE* outfile = NULL;

    infile = fopen(filename, "rb");
    if (infile == NULL) {
        printf("Error: unable to open file %s\n", "input.txt");
        exit(1);
    }

    int s = strlen(filename);
    char newName[100] = "";
    strncat(newName, filename, s-4);
    strcat(newName,"-glitch.ppm");

    printf("Writing file %s",newName);
    outfile = fopen(newName, "wb");
    if (outfile == NULL) {
        printf("Error: unable to open outfile\n");
        exit(1);
    }

    int ch, n=0;  
    ch = getc(infile);    
    while ( n < 4 ) {
      if (ch == '\n')
        n++; 
      putc(ch, outfile);  
      ch = getc(infile);      
    }

    for (int i=0 ; i<h ; i++){
        for (int j=0 ; j<w ; j++){
            fwrite(&pxs[i][j],sizeof(struct ppm_pixel), 1,outfile);
        }
     }

    fclose(infile);
    fclose(outfile);
}