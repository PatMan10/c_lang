#include <stdio.h>

#include "lib.h"

/*
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the
 * same tab stops as for detab. When either a tab or a single blank would suffice
 * to reach a tab stop, which should be given preference?
 */

int main() {
  char str[] = "a   str   ing \tx  s  asd  s";
  Counts counts = count_blanks(str, 3);
  int size = get_buffer_size(counts);
  char buffer[size] = {};
  
  entab(str, buffer, counts);  
  printf("before: %s\nafter: %s\n", str, buffer);

  return 0;
}
