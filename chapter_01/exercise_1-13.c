#include <stdlib.h>
#include <stdio.h>

/*
 * Histogram of word lengths.
 */

int blank(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}

void print_barchart(int lengths[], int size) {
  for (int idx = 0; idx < size; ++idx) {
    int cur_len = lengths[idx];
    for (int len = 0; len < cur_len; ++len) {
      putchar('-');
      if (len == cur_len - 1) {
        printf("%d", cur_len);
        putchar('\n');
      }
    }
  }
}

int main() {
  int cur, prev = ' ';
  int length = 0, size = 0;
  const int MAX = 10;
  int lengths[MAX] = {};

  while ((cur = getchar()) != EOF) {
    if (size == MAX) {
      break;
    }

    if (!blank(cur))
      ++length;

    if (blank(cur) && !blank(prev)) {
      // system("clear");
      lengths[size] = length;
      ++size;
      length = 0;
    }
    prev = cur;
  }

  print_barchart(lengths, size);

  return 0;
}
