#include <stdio.h>
#include <stdlib.h>

/*
 * Remove preceding and trailing white space then print line.
 */

int read_line(char line[], int max_length);
void trim(char string[]);

int main() {
  const int size = 101;
  char string[size] = {};
  int length = 0;

  while ((length = read_line(string, size)) > 0) {
    trim(string);
    printf("'%s'\n", string);
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

// remove preceding and trailing white space from [string]
void trim(char string[]) {
  int first = 0, last = 0, a = 0, b = 0, c;

  // find index of first and last non-blank characters
  while (c = string[a]) {
    if (!first && !blank(c)) {
      first = a;
    }
    if (!blank(c)) {
      last = a;
    }
    ++a;
  }

  int buff_size = a;
  int sub_size = last - first + 2; // +1 for 0 based and +1 for null byte
  char substr[sub_size] = {};

  // copy sub-string to substr
  b = first;
  for (a = 0; b <= last; ++a) {
    substr[a] = string[b];
    ++b;
  }

  // clear string
  for (a = 0; a < buff_size; a++) {
    string[a] = '\0';
  }

  // copy substr to string
  for (a = 0; a < sub_size; ++a) {
    string[a] = substr[a];
  }
  string[a] = '\0';
}
