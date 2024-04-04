#include <stdio.h>

/*
 * Replace tabs with spaces.
 */

int read_line(char[], int);
int count_tabs(char[]);
int str_len(char[]);
void tabs_to_spaces(char[], char[], int);

int main() {
  int size = 100;
  char buffer[size] = {};

  int a = 0, spaces = 2;
  while ((a = read_line(buffer, size)) != 0) {
    int spaced_size = spaces * count_tabs(buffer) + str_len(buffer);
    char spaced_buffer[spaced_size] = {};

    tabs_to_spaces(buffer, spaced_buffer, spaces);
    printf("'%s'\n", spaced_buffer);
  }
  
  return 0;
}

// read up to [max_length] characters into [line]
int read_line(char buffer[], int size) {
  int i, c;
  for (i = 0; i < size - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
    buffer[i] = c;
  }
  buffer[i] = '\0';
  return i;
}

// count '\t' in [buffer]
int count_tabs(char buffer[]) {
  int tabs = 0, i = 0, c;
  while (c = buffer[i]) {
    if (c == '\t') {
      ++tabs;
    }
    ++i;
  }
  return tabs;
}

// determine length of [buffer]
int str_len(char buffer[]) {
  int i = 0;
  while (buffer[i]) {
    ++i;
  }
  return i;
}

// copy content from [string] to [buffer] replacing '\t' with [spaces] 
void tabs_to_spaces(char string[], char buffer[], int spaces) {
  int a = 0, b = 0, c;
  while (c = string[a]) {
    if (c == '\t') {
      for (int x = 0; x < spaces; ++x) {
        buffer[b] = ' ';
        ++b;
      }
    } else {
      buffer[b] = c;
      ++b;
    }
    ++a;
  }
}
