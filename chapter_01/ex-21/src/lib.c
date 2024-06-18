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
  return c == ' ';
}

bool tab(char c) {
  return c == '\t';
}

bool blank(char c) {
  return space(c) || tab(c);
}

bool blank_sequence(char prev, char cur) {
  int one = !blank(prev) && blank(cur);
  int two = blank(prev) && blank(cur);
  return one || two;
}


Counts counts_new(int spaces_per_tab) {
  Counts c = {
    spaces_per_tab: spaces_per_tab,
    string_length: 0,
    total_spaces: 0,
    total_tabs: 0,
    total_sequences: 0,
    shortest_sequence: INT_MAX,
    shortest_sequence_total_spaces: INT_MAX,
    shortest_sequence_total_tabs: INT_MAX,
    tab_stop: 0,
  };
  return c;
}

char* counts_to_str(Counts counts) {
  char* buffer = malloc(sizeof(char) * 1024);
  sprintf(
    buffer,
    "spaces per tab = %d\nstring length = %d\ntotal spaces = %d\ntotal tabs = %d\ntotal sequences = %d\nshortest sequence = %d\ntotal spaces in shortest sequence = %d\ntotal tabs in shortest sequence = %d\ntab stop = %d\n",
    counts.spaces_per_tab,
    counts.string_length,
    counts.total_spaces,
    counts.total_tabs,
    counts.total_sequences,
    counts.shortest_sequence,
    counts.shortest_sequence_total_spaces,
    counts.shortest_sequence_total_tabs,
    counts.tab_stop
  ); 
  return buffer;
}


Counts count_blanks(char buffer[], int spaces_per_tab) {
  int i = 0, prev, cur;
  int shortest_sequence = 0, shortest_spaces = 0, shortest_tabs = 0;
  bool in_sequence = false;
  Counts counts = counts_new(spaces_per_tab);

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
  counts.string_length = i;
  if (in_sequence && shortest_sequence < counts.shortest_sequence) {
    counts.shortest_sequence = shortest_sequence;
    counts.shortest_sequence_total_spaces = shortest_spaces;
    counts.shortest_sequence_total_tabs = shortest_tabs;
  }
  in_sequence = false;
  shortest_sequence = 0;
  shortest_spaces = 0;
  shortest_tabs = 0;
  counts.tab_stop = counts.shortest_sequence_total_tabs * spaces_per_tab + counts.shortest_sequence_total_spaces;

  return counts;
}

int get_buffer_size(Counts counts, int spaces_per_tab) {
  int char_count = counts.string_length - (counts.total_spaces + counts.total_tabs);
  int blank_stop = (counts.shortest_sequence_total_tabs * spaces_per_tab) + counts.shortest_sequence_total_spaces;
  int buffer_size = char_count + (counts.total_sequences * blank_stop);
  return buffer_size;
}

void entab(char from[], char to[], Counts counts) {
  int f_idx = 0, t_idx = 0;
  int cur, prev;

  int s_len = counts.string_length;

  while(f_idx < counts.string_length && (cur = from[f_idx])) {
    if (blank_sequence(prev, cur)) {
      printf("'%c' in blank sequence\n", cur);
      for (int a = 1; a <= counts.tab_stop; a++) {
        to[t_idx] = ' ';
        ++t_idx;
      }
      while(blank(cur = from[f_idx])) {
        printf("'%c'", cur);
        ++f_idx;
        prev = cur;
      }
      printf("\n continue\n");
      continue;
    }

    if (!blank(cur)) {
      printf("%c char\n", cur);
      to[t_idx] = cur;
    }
    ++f_idx;
    ++t_idx;
    prev = cur;
  }
  printf("f_idx = %d\nt_idx = %d\n", f_idx, t_idx);
}
