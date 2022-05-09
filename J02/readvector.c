#include <stdio.h>
#include <stdlib.h>

// readvector opens and reads the given file
// The size of the vector should be stored in the parameter size
// The values should be returned in a flat float array
float* readvector(const char* filename, int *size) {
  // todo: implement me
  FILE* infile = NULL;
  infile = fopen(filename, "r");
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    exit(1);
  }

  *size = fgetc(infile);
  float* vector = (float*) malloc (sizeof(float) * *size);
  for ( int i=0; getc(infile) != EOF; i++)
  {
    char line[32];
    fgets(line, sizeof(line), infile);
    vector[i] = atof(line);
    printf("%f\n", vector[i]);
  }

    fclose(infile);
    return vector ;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: readvector <filename>\n");
    exit(0);
  }

  int size = 0;
  float* vector = readvector(argv[1], &size);

  // todo: print vector values
  free(vector);
  return 0;


}
