#include <stdio.h>

/*
 * Count lines, words and characters in input.
 */

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */

int main() {
  int cur, prev, lines, words, chars, state;

  state = OUT;
  lines = words = chars = 0;
  prev = ' ';
  while ((cur = getchar()) != EOF) {
    ++chars;

    if (cur == '\n')
      ++lines;

    int cur_is_blank = cur == ' ' || cur == '\t' || cur == '\n';
    int prev_is_blank = prev == ' ' || prev == '\t' || prev == '\n';

    if (cur_is_blank)
      state = OUT;

    if (!cur_is_blank && prev_is_blank) {
      state = IN;      
      ++words;
    }
    prev = cur;
  }
  printf("%d char(s)\n", chars);
  printf("%d word(s)\n", words);
  printf("%d line(s)\n", lines);
  
  return 0;
}
