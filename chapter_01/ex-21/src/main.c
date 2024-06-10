#include <stdio.h>

#include "lib.h"

/*
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the
 * same tab stops as for detab. When either a tab or a single blank would suffice
 * to reach a tab stop, which should be given preference?
 */

int main() {
  char str[] = "some string";
  char c;
  int i = 0;
  while (c = str[i]) {
    if (c)
      printf("%c\n", c);
    if (c == '\0')
      printf("AAAAAAAAAA\n");
    ++i;
  }
  if (c == '\0')
    printf("AAAAAAAAAA\n");
  // Counts c = counts_new();
  // c.total_spaces = 5;
  // c.total_tabs = 10;
  // char* str = counts_to_str(c);
  printf(str);
  // int size = 100;
  // char buffer[size] = {};

  // printf("%d\n", str_len("hello"));

  // int a = 0, spaces = 2;
  // while ((a = read_line(buffer, size)) != 0) {
  //   int spaced_size = spaces * count_tabs(buffer) + str_len(buffer);
  //   char spaced_buffer[spaced_size] = {};

  //   printf("'%s'\n", spaced_buffer);
  // }
  
  return 0;
}
