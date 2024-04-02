#include <stdio.h>
#include <stdlib.h>

/*
 * Print longest line.
 */

#define MAX_LENGTH 11

int read_line(char line[], int max_length);
void copy(char from[], char to[]);

int main() {
  char max_line[MAX_LENGTH] = {},
       cur_line[MAX_LENGTH] = {};
  int max_length = 0, cur_length;

  while ((cur_length = read_line(cur_line, MAX_LENGTH)) > 0) {
    printf("%d %s\n", cur_length, cur_line);
    if (cur_length >= max_length) {
      copy(cur_line, max_line);
      max_length = cur_length;
    }
  }

  if (max_length) {
    system("clear");
    printf("max length: %d\n", max_length);
    printf("max line: %s\n", max_line);
  } else {
    printf("no lines...\n");
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
