#include <stdbool.h>
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

bool space(char c) {
  return c == ' ' ? true : false;
}

bool tab(char c) {
  return c == '\t' ? true : false;
}

bool blank(char c) {
  return space(c) || tab(c) ? true : false;
}

bool blank_sequence(char prev, char cur) {
  int one = !blank(prev) && blank(cur);
  int two = blank(prev) && blank(cur);
  return one || two ? true : false;
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

void counts_print(Counts counts) {
  printf("total spaces = %d\n", counts.total_spaces);
  printf("total tabs = %d\n", counts.total_tabs);
  printf("total sequences = %d\n", counts.total_sequences);
  printf("longest sequence = %d\n", counts.longest_sequence);
  printf("total spaces in longest sequence = %d\n", counts.total_spaces_in_longest_sequence);
  printf("total tabs in longest sequence = %d\n", counts.total_tabs_in_longest_sequence);
}


Counts count_blanks(char buffer[]) {
  int i = 0, prev, cur;
  int longest_sequence = 0, longest_spaces = 0, longest_tabs = 0;
  bool in_sequence = 0;
  Counts counts = counts_new();

  while (cur = buffer[i]) {
    // total spaces
    if (space(cur)) {
      ++counts.total_spaces;
    }
    // total tabs
    if (tab(cur)) {
      ++counts.total_tabs;
    }
    // longest sequence of blanks
    if (blank_sequence(prev, cur)) {
      if (!in_sequence) {
        in_sequence = true;
        ++counts.total_sequences;
      }
      ++longest_sequence;
      // total spaces in longest sequence
      if (space(cur)) {
        ++longest_spaces;
      }
      // total tabs in longest sequence
      if (tab(cur)) {
        ++longest_tabs;
      }

      if (longest_sequence > counts.longest_sequence) {
        counts.longest_sequence = longest_sequence;
        counts.total_spaces_in_longest_sequence = longest_spaces;
        counts.total_tabs_in_longest_sequence = longest_tabs;
      }
    } else {
      in_sequence = false;
      longest_sequence = 0;
      longest_spaces = 0;
      longest_tabs = 0;
    }
    ++i;
    prev = cur;
  }
  return counts;
}

int calculate_blank_stop(int counts[3], int n_spaces) {
  return counts[1] + counts[2] * n_spaces;
}
