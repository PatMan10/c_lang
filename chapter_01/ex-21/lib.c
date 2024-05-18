#include <stdio.h>

int read_line(char buffer[], int size) {
  int i, c;
  for (i = 0; i < size - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
    buffer[i] = c;
  }
  buffer[i] = '\0';
  return i;
}

int str_len(char buffer[]) {
  int i = 0;
  while (buffer[i]) {
    ++i;
  }
  return i;
}

int space(char c) {
  return c == ' ' ? 1 : 0;
}

int tab(char c) {
  return c == '\t' ? 1 : 0;
}

int blank(char c) {
  return space(c) || tab(c) ? 1 : 0;
}

int blank_seq(char prev, char cur) {
  int one = !blank(prev) && blank(cur);
  int two = blank(prev) && blank(cur);
  return one || two ? 1 : 0;
}


void count_blanks(char buffer[], int counts[5]) {
  int i = 0, prev, cur;
  int max_seq = 0, max_spaces = 0, max_tabs = 0;
  while (cur = buffer[i]) {
    // total spaces
    if (space(cur)) {
      ++counts[0];
    }
    // total tabs
    if (tab(cur)) {
      ++counts[1];
    }
    // longest sequence of blanks
    if (blank_seq(prev, cur)) {
      ++max_seq;
      // total spaces in longest sequence
      if (space(cur)) {
        ++max_spaces;
      }
      // total tabs in longest sequence
      if (tab(cur)) {
        ++max_tabs;
      }

      if (max_seq > counts[2]) {
        counts[2] = max_seq;
        counts[3] = max_spaces;
        counts[4] = max_tabs;
      }
    } else {
      max_seq = 0;
      max_spaces = 0;
      max_tabs = 0;
    }
    ++i;
    prev = cur;
  }
}
