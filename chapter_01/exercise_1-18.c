#include <stdio.h>
#include <stdlib.h>

/*
 * Remove preceding and trailing white space then print line.
 */

int read_line(char line[], int max_length);
void trim(char from[], char to[]);

int main() {
  const int size = 101;
  char buffer[size] = {},
       trimmed[size] = {};
  int length = 0;

  while ((length = read_line(buffer, size)) > 0) {
    trim(buffer, trimmed);
    printf("%s\n", trimmed);
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

int blank(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}

// copy characters [from] [to], remove preceding and trailing white space
void trim(char from[], char to[]) {
  int first = 0, last = 0, i = 0, c;

  // find index of first and last non-blank characters
  while (c = from[i]) {
    if (!first && !blank(c)) {
      first = i;
    }
    if (!blank(c)) {
      last = i;
    }
    ++i;
  }

  i = 0;
  while (c = from[i]) {
    if (i >= first && i <= last) {
      to[i] = c;
      printf("'%c'", to[i]);
    }
    if (i > last) {
      to[i] = '\0';
      printf("\nfrom: '%s'\nto: '%s'\n", from, to);
      return;
    }
    ++i;
  }
}
