#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {

  void *intial = sbrk(0); 
  printf("The initial top of the heap is %p.\n", intial );
  void *current = sbrk(0); 
  printf("The current top of the heap is %p.\n", current );
  int increase = current - intial;
  printf("Increased by %d (0x%x) bytes\n",increase, increase);

  return 0 ;
}

