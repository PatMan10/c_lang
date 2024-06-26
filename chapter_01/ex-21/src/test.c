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
  Counts c = counts_new(2);
  cr_assert_eq(c.spaces_per_tab, 2);
  cr_assert_eq(c.total_spaces, 0);
  cr_assert_eq(c.total_tabs, 0);
  cr_assert_eq(c.total_sequences, 0);
  cr_assert_eq(c.shortest_sequence, INT_MAX);
  cr_assert_eq(c.shortest_sequence_total_spaces, INT_MAX);
  cr_assert_eq(c.shortest_sequence_total_tabs, INT_MAX);
  cr_assert_eq(c.tab_stop, 0);
}

// ####################
// counts_to_str
// ####################
Test(counts_to_str, yes) {
  Counts c = counts_new(2);
  c.string_length = 99;
  c.total_spaces = 100;
  c.total_tabs = 10;
  c.shortest_sequence = 0;
  c.shortest_sequence_total_spaces = 25;
  c.shortest_sequence_total_tabs = 0;

  char* result = counts_to_str(c);
  char* expected = "spaces per tab = 2\nstring length = 99\ntotal spaces = 100\ntotal tabs = 10\ntotal sequences = 0\nshortest sequence = 0\ntotal spaces in shortest sequence = 25\ntotal tabs in shortest sequence = 0\ntab stop = 0\n";
  cr_assert_eq(strcmp(result, expected), 0);

  free(result);
}


// ####################
// count_blanks
// ####################
Test(count_blanks, _1) {
  char str[] = "a string \t";
  Counts counts = count_blanks(str, 2);

  cr_assert_eq(counts.spaces_per_tab, 2);
  cr_assert_eq(counts.string_length, 10);
  cr_assert_eq(counts.total_spaces, 2);
  cr_assert_eq(counts.total_tabs, 1);
  cr_assert_eq(counts.total_sequences, 2);
  cr_assert_eq(counts.shortest_sequence, 1);
  cr_assert_eq(counts.shortest_sequence_total_spaces, 1);
  cr_assert_eq(counts.shortest_sequence_total_tabs, 0);
  cr_assert_eq(counts.tab_stop, 1);
}

Test(count_blanks, _2) {
  char str[] = "a\t string \t\t a";
  Counts counts = count_blanks(str, 2);

  cr_assert_eq(counts.spaces_per_tab, 2);
  cr_assert_eq(counts.string_length, 14);
  cr_assert_eq(counts.total_spaces, 3);
  cr_assert_eq(counts.total_tabs, 3);
  cr_assert_eq(counts.total_sequences, 2);
  cr_assert_eq(counts.shortest_sequence, 2);
  cr_assert_eq(counts.shortest_sequence_total_spaces, 1);
  cr_assert_eq(counts.shortest_sequence_total_tabs, 1);
  cr_assert_eq(counts.tab_stop, 3);
}

Test(count_blanks, _3) {
  char str[] = "\t     xxx  \t\t xx \t x";
  Counts counts = count_blanks(str, 4);

  cr_assert_eq(counts.spaces_per_tab, 4);
  cr_assert_eq(counts.string_length, 20);
  cr_assert_eq(counts.total_spaces, 10);
  cr_assert_eq(counts.total_tabs, 4);
  cr_assert_eq(counts.total_sequences, 3);
  cr_assert_eq(counts.shortest_sequence, 3);
  cr_assert_eq(counts.shortest_sequence_total_spaces, 2);
  cr_assert_eq(counts.shortest_sequence_total_tabs, 1);
  cr_assert_eq(counts.tab_stop, 6);
}

Test(count_blanks, _4) {
  char str[] = "a     string \t\t";
  Counts counts = count_blanks(str, 4);

  cr_assert_eq(counts.spaces_per_tab, 4);
  cr_assert_eq(counts.string_length, 15);
  cr_assert_eq(counts.total_spaces, 6);
  cr_assert_eq(counts.total_tabs, 2);
  cr_assert_eq(counts.total_sequences, 2);
  cr_assert_eq(counts.shortest_sequence, 3);
  cr_assert_eq(counts.shortest_sequence_total_spaces, 1);
  cr_assert_eq(counts.shortest_sequence_total_tabs, 2);
  cr_assert_eq(counts.tab_stop, 9);
}

// ####################
// get_buffer_size
// ####################
Test(get_buffer_size, _1) {
  char str[] = "a string \t";
  Counts counts = count_blanks(str, 2);
  int buffer_size = get_buffer_size(counts);

  cr_assert_eq(buffer_size, 10);
}

Test(get_buffer_size, _2) {
  char str[] = "a   string \t";
  Counts counts = count_blanks(str, 2);
  int buffer_size = get_buffer_size(counts);

  cr_assert_eq(buffer_size, 14);
}

Test(get_buffer_size, _3) {
  char str[] = "a     string \t\t";
  Counts counts = count_blanks(str, 4);
  int buffer_size = get_buffer_size(counts);

  cr_assert_eq(buffer_size, 26);
}

Test(get_buffer_size, _4) {
  char str[] = "\t    xxx  \t\t xx \t   x";
  Counts counts = count_blanks(str, 4);
  int buffer_size = get_buffer_size(counts);

  cr_assert_eq(buffer_size, 31);
}

// ####################
// entab
// ####################
Test(entab, _1) {
  char str[] = "a string \tx";
  Counts counts = count_blanks(str, 2);
  int size = get_buffer_size(counts);
  char buffer[size] = {};
  
  entab(str, buffer, counts);

  char expected[] = "a string x";
  cr_assert_eq(strcmp(buffer, expected), 0);
}

Test(entab, _2) {
  char str[] = "a   string \t";
  Counts counts = count_blanks(str, 2);
  int size = get_buffer_size(counts);
  char buffer[size] = {};
  
  entab(str, buffer, counts);

  char expected[] = "a   string   ";
  cr_assert_eq(strcmp(buffer, expected), 0);
}

Test(entab, _3) {
  char str[] = "a   str   ing \tx  ";
  Counts counts = count_blanks(str, 4);
  int size = get_buffer_size(counts);
  char buffer[size] = {};
  
  entab(str, buffer, counts);

  char expected[] = "a     str     ing     x     ";
  cr_assert_eq(strcmp(buffer, expected), 0);
}

Test(entab, _4) {
  char str[] = "a   str   ing \tx  s  asd  s";
  Counts counts = count_blanks(str, 3);
  int size = get_buffer_size(counts);
  char buffer[size] = {};
  
  entab(str, buffer, counts);

  char expected[] = "a    str    ing    x    s    asd    s";
  cr_assert_eq(strcmp(buffer, expected), 0);
}
