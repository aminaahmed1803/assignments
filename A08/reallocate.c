#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {
  void * intial = sbrk(0);
  printf("The intial top of the heap is %p.\n", intial );
  int * test = NULL;
  for (int i= 0 ; i<10 ; i++){
    test = malloc(100);
    if( test == NULL) {
            fprintf(stderr , "malloc failed\n");
	    return (1);
    }
    *test = 233;
    free(test);
  }
  void *current = sbrk(0);
  printf("The current top of the heap is %p.\n", current );
  int size = current - intial;
  printf("Bytes Allocated at the End:  %d (0x%x) bytes\n",size, size);	
  return 0 ;
}

