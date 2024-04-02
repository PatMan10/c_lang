#include <stdio.h>
#include <stdlib.h>

/*
 * Print lines longer than X.
 */

#define MIN_LENGTH 3

int read_line(char line[], int max_length);

int main() {
  const int buff_size = 101;
  char line[buff_size] = {};
  int length = 0;

  while ((length = read_line(line, buff_size)) > 0) {
    if (length >= MIN_LENGTH) {
      printf("%d %s\n", length, line);
    }
  }

  return 0;
}

// read up to [max_length] characters into [line]
int read_line(char line[], int max_length) {
  int i, c;
  for (i = 0; i < max_length - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
    line[i] = c;
  }
  line[i] = '\0';
  return i;
}
