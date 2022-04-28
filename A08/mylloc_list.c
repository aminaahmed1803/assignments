#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int inUse;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  if (size == 0){
    return NULL;
  }
	struct chunk *next = flist ;
       	struct chunk *prev = NULL;
	while(next != NULL) {
		if (next->size >= size) {
			if(prev != NULL) {
			       	prev->next = next->next;
			} else {
				flist = next->next;
			}
			next->inUse = size;
			return (void*)(next + 1); 
		} else {
			prev = next;
			next = next->next;
	       	}
	}

	void *memory = sbrk(size + sizeof(struct chunk));
	if (memory == (void *)-1) { 
		return NULL;
	} else {
		struct chunk *cnk = (struct chunk*)memory;
	       	cnk->size = size ;
		cnk->inUse = size; 
		return (void*)(cnk + 1);
	}

}

void free(void *memory) {
   if(memory != NULL) {
   /* we're jumping back one chunk position */
      struct chunk *cnk = (struct chunk*)((struct chunk*)memory - 1);
      cnk->inUse = 0;
      cnk->next = flist;
      flist = cnk;
   }
   return ;      
}

void fragstats(void* buffers[], int len) {
	int total=0, used=0, free=0;

	struct chunk *next = flist ;
	int ex_s = next->size-  next->inUse;
	int external=0, ex_b=0;

        while(next != NULL) {
	   free++;
	   if (next->inUse >0 ){
	   	int mem =next->size;
           	external +=  mem; 
	    	if (mem > ex_b) ex_b = mem;
	    	if (mem < ex_s) ex_s = mem;
	  }
           // printf("size: %d, inUse: %d\n",next->size, next->inUse);
	   next = next->next;
        }
	float average = external / free; 

	int internal=0, in_b=0, in_s=1000;
	for (int i=0 ; i<len ; i++)
	{
	
	   if (buffers[i] != NULL)
	   {
		used++;
		struct chunk *cnk = (struct chunk*)((struct chunk*)buffers[i] - 1);
		int s = cnk->size;
		internal += s;
		if (s > in_b) in_b = s;
                if (s < in_s) in_s = s;
		//printf("Allocated: %p\n", buffers[i]);
           }
	}
	total = free+used; 
	printf("Total blocks: %d, Free: %d, Used: %d\n",total, free, used );
	printf("Internal unused: total: %d average: %0.1f smallest: %d largest: %d\n", internal, average, in_s, in_b);
	average = external / used;
	printf("External unused: total: %d average: %0.1f smallest: %d largest: %d\n",external, average, ex_s,ex_b);
} 



