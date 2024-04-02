#include <stdio.h>
#include <stdlib.h>

/*
 * Print lines longer than X.
 */

#define MIN_LENGTH 3

int read_line(char line[], int max_length);
void copy(char from[], char to[]);

int main() {
  const int num_lines = 10, line_length = 11;
  char lines[num_lines][line_length] = {};
  int lengths[num_lines] = {};

  const int size = line_length;
  char buffer[size] = {};

  int length = 0;
  int idx = 0;
  while ((length = read_line(buffer, size)) > 0 && idx < num_lines) {
    if (length >= MIN_LENGTH ) {
      copy(buffer, lines[idx]);
      lengths[idx] = length;
      ++idx;
    }
  }

  system("clear");
  printf("%d lines longer than %d characters\n", idx, MIN_LENGTH);
  for (int i = 0; i < idx; ++i) {
    printf("%d %s\n", lengths[i], lines[i]);
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

// copy characters [from] [to]
void copy(char from[], char to[]) {
  int i = 0;
  while (from[i]) {
    to[i] = from[i];
    ++i;
  }
  to[i] = '\0';
}
