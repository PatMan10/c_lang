#include <stdio.h>

/*
 * Read input and print one word per line.
 */

int main() {
  int cur, prev;

  prev = ' ';
  while ((cur = getchar()) != EOF) {
    int cur_is_blank = cur == ' ' || cur == '\t' || cur == '\n';
    int prev_is_blank = prev == ' ' || prev == '\t' || prev == '\n';

    if (cur_is_blank && !prev_is_blank) {
      putchar('\n');
    }

    if (!cur_is_blank) {
      putchar(cur);
    }
    prev = cur;
  }
  
  return 0;
}
