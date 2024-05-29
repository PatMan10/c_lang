#include <stdio.h>

#include "lib.h"

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

int blank_sequence(char prev, char cur) {
  int one = !blank(prev) && blank(cur);
  int two = blank(prev) && blank(cur);
  return one || two ? 1 : 0;
}

Counts counts_new() {
  Counts c = {
    total_spaces: 0,
    total_tabs: 0,
    total_sequences: 0,
    longest_sequence: 0,
    total_spaces_in_longest_sequence: 0,
    total_tabs_in_longest_sequence: 0,
  };
  return c;
}


void count_blanks(char buffer[], int counts[5]) {
  int i = 0, prev, cur;
  int longest_sequence = 0, longest_spaces = 0, longest_tabs = 0;
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
    if (blank_sequence(prev, cur)) {
      ++longest_sequence;
      // total spaces in longest sequence
      if (space(cur)) {
        ++longest_spaces;
      }
      // total tabs in longest sequence
      if (tab(cur)) {
        ++longest_tabs;
      }

      if (longest_sequence > counts[2]) {
        counts[2] = longest_sequence;
        counts[3] = longest_spaces;
        counts[4] = longest_tabs;
      }
    } else {
      longest_sequence = 0;
      longest_spaces = 0;
      longest_tabs = 0;
    }
    ++i;
    prev = cur;
  }
}

int calculate_blank_stop(int counts[3], int n_spaces) {
  return counts[1] + counts[2] * n_spaces;
}
