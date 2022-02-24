#include <stdio.h>

int  toDec (int n, int i ) {
  if (n >=1)
  {
    return (n%10)*i + toDec(n/10, i*2);
  }
  return 0; 
}  

int main() {

  int binary; 
  printf("Enter 8 bits: ");
  scanf("%d", &binary);
  int dec = toDec(binary, 1);
  printf("Your character is: %c\n", dec);

  return 0;
}
