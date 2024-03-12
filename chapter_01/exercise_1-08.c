#include <stdio.h>

/*
 * Character Input and Output
 */

int main() {
  int blanks = 0;
  int c;

  while ((c = getchar()) != EOF)
    if (c == ' '|| c == '\t' || c == '\n')
      ++blanks;
  printf("I count %d blanks.\n", blanks);
  
  return 0;
}
