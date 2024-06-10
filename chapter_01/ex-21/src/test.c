#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "lib.h"

// ####################
// str_len
// ####################
Test(str_len, pass) {
  int result = str_len("");
  cr_assert_eq(result, 0);

  result = str_len("a");
  cr_assert_eq(result, 1);

  result = str_len("abc");
  cr_assert_eq(result, 3);
}

// ####################
// space
// ####################
Test(space, yes) {
  char c = ' ';
  cr_assert_eq(space(c), true);
}

Test(space, no) {
  char c = '\t';
  cr_assert_eq(space(c), false);
}

// ####################
// tab
// ####################
Test(tab, yes) {
  char c = '\t';
  cr_assert_eq(tab(c), true);
}

Test(tab, no) {
  char c = ' ';
  cr_assert_eq(tab(c), false);
}

// ####################
// blank
// ####################
Test(blank, yes) {
  char c = ' ';
  cr_assert_eq(blank(c), true);

  c = '\t';
  cr_assert_eq(blank(c), true);
}

Test(blank, no) {
  char c = 'a';
  cr_assert_eq(blank(c), false);

  c = 'z';
  cr_assert_eq(blank(c), false);
}

// ####################
// blank_sequence
// ####################
Test(blank_sequence, yes) {
  char prev = 'a', cur = ' ';
  cr_assert_eq(blank_sequence(prev, cur), true);

  prev = '\t', cur = ' ';
  cr_assert_eq(blank_sequence(prev, cur), true);
}

Test(blank_sequence, no) {
  char prev, cur = 'a';
  cr_assert_eq(blank_sequence(prev, cur), false);

  prev = ' ', cur = 'a';
  cr_assert_eq(blank_sequence(prev, cur), false);

  prev = 'a', cur = 'b';
  cr_assert_eq(blank_sequence(prev, cur), false);
}

// ####################
// counts_new
// ####################
Test(counts_new, yes) {
  Counts c = counts_new();
  cr_assert_eq(c.total_spaces, 0);
  cr_assert_eq(c.total_tabs, 0);
  cr_assert_eq(c.total_sequences, 0);
  cr_assert_eq(c.shortest_sequence, INT_MAX);
  cr_assert_eq(c.shortest_sequence_total_spaces, INT_MAX);
  cr_assert_eq(c.shortest_sequence_total_tabs, INT_MAX);
}

// ####################
// counts_to_str
// ####################
Test(counts_to_str, yes) {
  Counts c = counts_new();
  c.string_length = 99;
  c.total_spaces = 100;
  c.total_tabs = 10;
  c.shortest_sequence = 0;
  c.shortest_sequence_total_spaces = 25;
  c.shortest_sequence_total_tabs = 0;

  char* result = counts_to_str(c);
  char* expected = "string length = 99\ntotal spaces = 100\ntotal tabs = 10\ntotal sequences = 0\nshortest sequence = 0\ntotal spaces in shortest sequence = 25\ntotal tabs in shortest sequence = 0\n";
  cr_assert_eq(strcmp(result, expected), 0);

  free(result);
}


// ####################
// count_blanks
// ####################
Test(count_blanks, _1) {
  char str[] = "a string \t";
  Counts counts = count_blanks(str);

  cr_assert_eq(counts.string_length, 10);
  cr_assert_eq(counts.total_spaces, 2);
  cr_assert_eq(counts.total_tabs, 1);
  cr_assert_eq(counts.total_sequences, 2);
  cr_assert_eq(counts.shortest_sequence, 1);
  cr_assert_eq(counts.shortest_sequence_total_spaces, 1);
  cr_assert_eq(counts.shortest_sequence_total_tabs, 0);
}

Test(count_blanks, _2) {
  char str[] = "a\t string \t\t a";
  Counts counts = count_blanks(str);

  cr_assert_eq(counts.string_length, 14);
  cr_assert_eq(counts.total_spaces, 3);
  cr_assert_eq(counts.total_tabs, 3);
  cr_assert_eq(counts.total_sequences, 2);
  cr_assert_eq(counts.shortest_sequence, 2);
  cr_assert_eq(counts.shortest_sequence_total_spaces, 1);
  cr_assert_eq(counts.shortest_sequence_total_tabs, 1);
}

Test(count_blanks, _3) {
  char str[] = "\t     xxx  \t\t xx \t x";
  Counts counts = count_blanks(str);

  cr_assert_eq(counts.string_length, 20);
  cr_assert_eq(counts.total_spaces, 10);
  cr_assert_eq(counts.total_tabs, 4);
  cr_assert_eq(counts.total_sequences, 3);
  cr_assert_eq(counts.shortest_sequence, 3);
  cr_assert_eq(counts.shortest_sequence_total_spaces, 2);
  cr_assert_eq(counts.shortest_sequence_total_tabs, 1);
}

Test(count_blanks, _4) {
  char str[] = "a     string \t\t";
  Counts counts = count_blanks(str);

  cr_assert_eq(counts.string_length, 15);
  cr_assert_eq(counts.total_spaces, 6);
  cr_assert_eq(counts.total_tabs, 2);
  cr_assert_eq(counts.total_sequences, 2);
  cr_assert_eq(counts.shortest_sequence, 3);
  cr_assert_eq(counts.shortest_sequence_total_spaces, 1);
  cr_assert_eq(counts.shortest_sequence_total_tabs, 2);
}

// ####################
// get_blank_stop
// ####################
Test(get_blank_stop, _1) {
  char str[] = "a string \t";
  Counts counts = count_blanks(str);
  int blank_stop = get_blank_stop(counts, 2);

  cr_assert_eq(blank_stop, 1);
}

Test(get_blank_stop, _2) {
  char str[] = "a   string \t";
  Counts counts = count_blanks(str);
  int blank_stop = get_blank_stop(counts, 2);

  cr_assert_eq(blank_stop, 3);
}

Test(get_blank_stop, _3) {
  char str[] = "a     string \t\t";
  Counts counts = count_blanks(str);
  int blank_stop = get_blank_stop(counts, 4);

  cr_assert_eq(blank_stop, 9);
}
