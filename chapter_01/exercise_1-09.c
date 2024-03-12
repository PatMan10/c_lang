#include <stdio.h>

/*
 * Character Input and Output
 */

int main() {
  int blanks = 0;
  int c;

  while ((c = getchar()) != EOF) {
    int c_is_blank = c == ' '|| c == '\t' || c == '\n';

    if (c_is_blank) {
      ++blanks;
      if (blanks > 1) continue;
    } else {
      blanks = 0;
    }

    putchar(c);
  }
  
  return 0;
}
