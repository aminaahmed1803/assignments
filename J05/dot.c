#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000 

int dotproduct2 = 0;

struct threadData {
  int* u;
  int* v;
  int start;
  int stop;
  int dp;
};

void dotprod(void* threadData_i) {
  struct threadData * data = (struct threadData*) threadData_i;
  //printf("start: %d, stop: %d\n", data->start, data->stop);
  for (int i = data->start; i < data->stop; i++) {
    int x= data->u[i];
    int y = data->v[i];
    data->dp += x*y;
    printf("u: %d, v: %d\n", data->u[i], data->v[i]);
  }
  printf("dp: %d\n",data->dp);
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int v[SIZE];
  int u[SIZE];
  int dotproduct = 0;
   
  for (int i = 0; i < SIZE; i++) {
    v[i] = rand() % 1000 - 500;
    u[i] = rand() % 1000 - 500;
    printf("u: %d, v: %d\n", u[i], v[i]);
    dotproduct += u[i] * v[i];
  }
  printf("Ground truth dot product: %d\n", dotproduct);

  // TODO: Implement your thread solution here
  // int dp = 0;
  pthread_t* tids = malloc(sizeof(pthread_t) * 4);
  struct threadData* dataArr = malloc(sizeof(struct threadData) * 4);
  for (int i=0; i < 4; i++) {
    pthread_t thread = NULL;
    tids[i] = thread;
    struct threadData threadData_i = {u, v, i*(SIZE/4), (i+1)*(SIZE/4), 0};
    dataArr[i] = threadData_i;
    pthread_create(&tids[i], NULL, (void*) dotprod, (void*) &dataArr[i]);
  }

  for (int i=0; i < 4; i++) {
    pthread_join(tids[i], NULL);
  }

  for (int i=0; i < 4; i++) {
    dotproduct2 += dataArr[i].dp;
  }
  
  printf("Test with 4 threads\n");
  
  printf("Answer with threads: %d\n", dotproduct2);
  return 0;
}
