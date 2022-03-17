#include <stdio.h>
#include <string.h>


int swapBits(int a)
{
  int n = a;

  int first = n%2;
  n = n/2;
  int sec = n%2; 
  n = n/2;
  int third = n%2;
  n = n/2;

  if (sec == 1)
    n = (n*2) + 1;
  else 
    n = n*2; 

  if (third == 1)
    n = (n*2) + 1;
  else 
    n = n*2; 

  if (first == 1)
    n = (n*2) + 1;
  else 
    n = n*2; 

  return n;
}

int main() {

  char message[100]; 
  printf("Please enter a phrase: ");
  fgets(message, 100, stdin);

  for (int i=0 ; message[i]!='\0' ; i++)
  {
    int temp = message[i];
    temp = swapBits(temp);
    message[i] = temp;

  }
  printf("\n%s", message);
  return 0;
}
