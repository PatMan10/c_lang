#include <stdio.h>

int main() {
  int blank_c = 0;
  int c;
  while ((c = getchar()) != EOF)
    if (c == ' '|| c == '\t' || c == '\n')
      ++blank_c;
  printf("I count %d blanks.\n", blank_c);
}
