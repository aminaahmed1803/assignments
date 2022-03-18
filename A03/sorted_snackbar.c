//---------------------------------------------------------------------
// sorted_snackbar.c 
// CS223 - Spring 2022
// Ask the user for a list of snacks and store them in alphabetical order
// Name: Amina Ahmed
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  int quantity;
  float cost;
  struct snack* next;
};


// Insert a new node to a list (implemented as a linked list). 
// The new node should store the given properties
// Param snacks: the first item in the list (NULL if empty)
// Param name: the snack name (max length is 32 characters)
// Param quantity: the snack quantity
// Param cost: the snack cost
// Returns the first item in the list
struct snack* insert_sorted(struct snack* snacks, const char* name, int quantity, float cost) {

  //head is empty
  if (snacks == NULL)
  {
    snacks = (struct snack*)malloc(sizeof(struct snack)); 
    strcpy(snacks-> name, name);
    snacks-> quantity = quantity;
    snacks-> cost = cost;
    snacks->next = NULL;
    return snacks;
  }
  //new snack is smallest
 /* else if ( strcmp (name, snacks->name) < 0)
  {
    struct snack * new =  (struct snack*)malloc(sizeof(struct snack)); 
    strcpy(new-> name, name);
    new-> quantity = quantity;
    new-> cost = cost;
    new->next = snacks;
    snacks = new; 
    return snacks;
  }*/
  //new snack is more than head and new snack is more than all
  else 
  {
    struct snack * s = snacks; 
    while( s->next != NULL  )
    {
      if(strcmp (name, s->next->name) < 0) break; 
      s = s->next;
    }
    struct snack * new =  (struct snack*)malloc(sizeof(struct snack)); 
    strcpy(new-> name, name);
    new-> quantity = quantity;
    new-> cost = cost;
    new->next =  s->next;
    s->next =  new;
    return snacks;
  }
}
 



struct snack* addsnack(struct snack* head)
{ 
  char name[32] = " " ;
  int quantity = 0;
  float cost = 0;

  printf("\nEnter a name: ");
  scanf(" %s", name);

  printf("Enter a cost: ");
  scanf(" %f", &cost);

  printf("Enter a quantity: ");
  scanf(" %d", &quantity);

  head = insert_sorted(head, name, quantity, cost); 
  //free(name);
  return head; 
}


// Delete (e.g. free) all nodes in the given list of snacks
// Param snacks: the first node in the list (NULL if empty)
void clear(struct snack* snacks) {
  struct snack* crr = snacks;
  struct snack* top = snacks;
  while (crr != NULL) {
    crr = crr->next;
    free(top);
    top = crr;
  }
}

void printbar(struct snack* snacks) {
  printf("\n");
  struct snack * temp = snacks;
  for(int i; temp != NULL ;i++)
  {  
    printf("%d) %s          cost: $%0.2f     quantity: %d\n",i, temp->name, temp->cost, temp->quantity);
    temp = temp->next;
  }
}


int main() {
  int count; 
  printf("Enter a count: "); 
  scanf(" %d", &count);

  struct snack * head = NULL;

  for (int i = 0; i < count; i++)
    head = addsnack(head); 

  printbar(head);
  clear(head);
    
  return 0;
}

