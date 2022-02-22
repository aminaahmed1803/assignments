//---------------------------------------------------------------------
// match_braces.c 
// CS223 - Spring 2022
// Identify matched braces from a given file
// Name:
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char sym;
  int linenum;
  int colnum;
  struct node* next;
};

// Push a new node to a stack (implemented as a linked list). 
// The new node should store the given symbol, line number, and column number
// Param sym: a character symbol, '{' for this program
// Param line: the line number of the symbol
// Param line: the column number of the symbol
// Param top: the top node of the stack (NULL if empty)
// Returns the new top of the stack
struct node* push(char sym, int line, int col, struct node* top) {
  struct node * newtop = (struct node*)malloc(sizeof(struct node)); 
  newtop-> sym = sym;
  newtop->linenum = line;
  newtop->colnum = col;
  if (top == NULL)
    newtop->next = NULL;  
  else
    newtop->next = top;
  return newtop;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  if (top == NULL) return NULL;
  struct node * newtop = top->next; 
  free(top); 
  top = NULL;
  return newtop;
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {
  struct node * next = top->next;
  struct node * current = top;
  while(next!=NULL)
  {
    free(current);
    current = NULL;
    if (next == NULL) return;
    current = next;
    next = next->next;
  }
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {
  if (top == NULL) return;
  printf("\n");
  struct node * temp = top;
  for(int i=0; temp != NULL ;i++)
  {  
    printf("%d) line=%d column=%d sym=%c\n",i, top->linenum, top->colnum, top->sym);
    temp = temp->next;
  }
}

void matchBrace(char * filename)
{
  FILE* infile = NULL;
  infile = fopen(filename, "r");
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    exit(1);
  }

  struct node * top = NULL;

  int ch = 0, line=0, col = 0;  
  while (ch != EOF) {
    ch = getc(infile);   // read next char from the infile stream
    col++; 
    if (ch == '\n')
    {
      line++;
      col = 0; 
    }
    if (ch == '{')
    {
      top = push('{', line, col, top);
      //print(top);
    }
    if (ch == '}')
    {
      //print(top);
      if (top == NULL)
      {
        printf("Unmatched brace on Line %d and Column %d\n", line, col); 
      } 
      else 
      {
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n",top->linenum, top->colnum, line, col);
        top = pop(top); 
      } 
    }
  }
  fclose(infile); 
  while (top != NULL)
  {
    printf("Unmatched brace on Line %d and Column %d\n", top->linenum, top->colnum); 
    top = pop(top);
  }
}

int main(int argc, char* argv[]) {

  if (argc != 2)
  {
    printf("Usage: ./match_braces \n");
    exit(0);
  }
  char filename[32];
  strncpy(filename, argv[1], 32);
  matchBrace(filename);
  return 0;
}

