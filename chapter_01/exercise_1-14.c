#include <stdlib.h>
#include <stdio.h>

/*
 * Histogram of the frequencies of different alphabet characters.
 */

void print_barchart(int[], int[]);

#define COUNT 26 // Number of chars in alphabet
#define UPPER 39 // 'a' - 26 = 39 UTF-8
#define LOWER 71 // 'A' - 26 = 71 UTF-8

int main() {
  int lower[26] = {};
  int upper[26] = {};

  for (int i = 0; i < COUNT; ++i) {
    lower[i] = 0;
    upper[i] = 0;
  }

  int c, i;
  while ((c = getchar()) != EOF) {
   if (c >= 'A' && c <= 'Z') {
      i = c - COUNT - UPPER;
      ++upper[i];
   }
   if (c >= 'a' && c <= 'z') {
      i = c - COUNT - LOWER;
      ++lower[i];
   }
  }

  print_barchart(upper, lower);

  return 0;
}

void print_barchart(int upper[], int lower[]) {
  for (int idx = 0; idx < COUNT; ++idx) {
    int cur_len = upper[idx] + lower[idx];
    if (cur_len == 0) continue;
    printf("%c%c", idx + COUNT + UPPER, idx + COUNT + LOWER);
    for (int len = 0; len < cur_len; ++len) {
      putchar('-');
      if (len == cur_len - 1) {
        printf("%d", cur_len);
        putchar('\n');
      }
    }
  }
}
