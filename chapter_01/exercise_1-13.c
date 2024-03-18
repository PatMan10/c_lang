#include <stdlib.h>
#include <stdio.h>

/*
 * Histogram of word lengths.
 */

int blank(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}

int main() {
  int cur, prev = ' ', length = 0, size = 0;
  int lengths[100] = {};

  while ((cur = getchar()) != EOF) {

    if (!blank(cur))
      ++length;

    if (blank(cur) && !blank(prev)) {
      system("clear");
      lengths[size] = length;
      ++size;

      for (int w = 0; w < size; ++w) {
        for (int l = 0; l < lengths[w]; ++l) {
          if (l < length) putchar('~');
          if (l == length - 1) printf(" %d\n", length);
        }
        length = 0;
      }
    }
    prev = cur;
  }

  return 0;
}
