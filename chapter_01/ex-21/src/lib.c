#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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
    shortest_sequence: INT_MAX,
    shortest_sequence_total_spaces: INT_MAX,
    shortest_sequence_total_tabs: INT_MAX,
  };
  return c;
}

char* counts_to_str(Counts counts) {
  char* buffer = malloc(sizeof(char) * 1024);
  sprintf(
    buffer,
    "total spaces = %d\ntotal tabs = %d\ntotal sequences = %d\nshortest sequence = %d\ntotal spaces in shortest sequence = %d\ntotal tabs in shortest sequence = %d\n",
    counts.total_spaces,
    counts.total_tabs,
    counts.total_sequences,
    counts.shortest_sequence,
    counts.shortest_sequence_total_spaces,
    counts.shortest_sequence_total_tabs
  ); 
  return buffer;
}


Counts count_blanks(char buffer[]) {
  int i = 0, prev, cur;
  int shortest_sequence = 0, shortest_spaces = 0, shortest_tabs = 0;
  bool in_sequence = false;
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
    // shortest sequence of blanks
    if (blank_sequence(prev, cur)) {
      if (!in_sequence) {
        in_sequence = true;
        ++counts.total_sequences;
      }
      ++shortest_sequence;
      // total spaces in shortest sequence
      if (space(cur)) {
        ++shortest_spaces;
      }
      // total tabs in shortest sequence
      if (tab(cur)) {
        ++shortest_tabs;
      }
    } else {
      if (in_sequence && shortest_sequence < counts.shortest_sequence) {
        counts.shortest_sequence = shortest_sequence;
        counts.shortest_sequence_total_spaces = shortest_spaces;
        counts.shortest_sequence_total_tabs = shortest_tabs;
      }
      in_sequence = false;
      shortest_sequence = 0;
      shortest_spaces = 0;
      shortest_tabs = 0;
    }
    ++i;
    prev = cur;
  }
  return counts;
}

int calculate_blank_stop(int counts[3], int n_spaces) {
  return counts[1] + counts[2] * n_spaces;
}
