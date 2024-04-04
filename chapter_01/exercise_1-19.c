#include <stdio.h>
#include <stdlib.h>

/*
 * Reverse characters then print line.
 */

int read_line(char line[], int max_length);
void reverse(char buffer[]);

int main() {
  const int size = 101;
  char buffer[size] = {};
  int length = 0;

  while ((length = read_line(buffer, size)) > 0) {
    reverse(buffer);
    printf("%s\n", buffer);
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

// reverse characters in buffer
void reverse(char buffer[]) {
  if (!buffer[0]) return;

  int count = 0, a = 0, b = 0;
  // count chars in buffer
  while (buffer[a]) {
    ++count;
    ++a;
  }

  // copy chars from buffer to temp
  char temp[count] = {};
  for (a = 0; a < count; a++) {
    temp[a] = buffer[a];
  }

  // overwrite existing buffer with reverse
  a = 0, b = count - 1;
  while (a < count && b >= 0) {
    buffer[a] = temp[b];
    ++a;
    --b;
  }
}
