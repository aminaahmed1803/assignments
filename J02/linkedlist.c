#include <stdio.h>
#include <string.h>

struct cake {
  float cost;
  char flavor[16];
  struct cake* next;
};

struct cake makeCake(const char* flavor, float cost) {
  struct cake newCake;
  strncpy(newCake.flavor, flavor, 16);
  newCake.cost = cost;
  newCake.next = NULL;
  return newCake;
}

// todo: implement cheapestCake
void cheapestCake(struct cake* head){
  char cheapest[16]=" ";
  strcpy(cheapest,head->flavor);
  float price = head->cost;
  while (head != NULL){
    printf("cake: %s ($%.2f)\n", head->flavor,head->cost);
    if(head->cost<price){
      price = head->cost;
      strcpy(cheapest,head->flavor);
    }
    head = head->next;
  }
  printf("the cheapest cake is %s\n",cheapest);
  return;
}


int main() {
  struct cake cake1 = makeCake("red velvet", 2.00);
  struct cake cake2 = makeCake("chocolate", 1.75);
  struct cake cake3 = makeCake("mocha", 3.50);
  struct cake cake4 = makeCake("rainbow sprinkle", 5.25);
  // todo: define 4th cake

  cake1.next = &cake2;
  cake2.next = &cake3;
  cake3.next = &cake4;
  // draw stack and heap here
  cheapestCake(&cake1);
  // todo: call cheapestCake
  return 0;
}