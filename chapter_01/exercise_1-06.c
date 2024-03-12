#include <stdio.h>

/*
 * Character Input and Output
 */


int main() {
  int c;
  while ((c = getchar()) != EOF) {
    putchar(c);
  }
  printf("\nc != EOF -> %d\n", c != EOF);

  return 0;
}
