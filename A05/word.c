#include <stdio.h>

int main() {

  char word[4]; 
  printf("Enter 4 characters: ");
  scanf("%s", word);

  unsigned int a = word[0] << 24;
  unsigned int b = word[1] << 16;
  unsigned int c = word[2] << 8;
  unsigned int d = word[3];
  unsigned int total =  a | b | c | d;
  
  printf("Debug: %c = 0x%08x\nDebug: %c = 0x%08x\nDebug: %c = 0x%08x\nDebug: %c = 0x%08x\nYour number is: %d ( 0x%08x)", 
  word[3], d, word[2], c, word[1], b, word[0], a, total, total );

  return 0;
}
