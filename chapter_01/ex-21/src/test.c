#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  cr_assert_eq(space(c), 1);
}

Test(space, no) {
  char c = '\t';
  cr_assert_eq(space(c), 0);
}

// ####################
// tab
// ####################
Test(tab, yes) {
  char c = '\t';
  cr_assert_eq(tab(c), 1);
}

Test(tab, no) {
  char c = ' ';
  cr_assert_eq(tab(c), 0);
}

// ####################
// blank
// ####################
Test(blank, yes) {
  char c = ' ';
  cr_assert_eq(blank(c), 1);

  c = '\t';
  cr_assert_eq(blank(c), 1);
}

Test(blank, no) {
  char c = 'a';
  cr_assert_eq(blank(c), 0);

  c = 'z';
  cr_assert_eq(blank(c), 0);
}

// ####################
// blank_sequence
// ####################
Test(blank_sequence, yes) {
  char prev = 'a', cur = ' ';
  cr_assert_eq(blank_sequence(prev, cur), 1);

  prev = '\t', cur = ' ';
  cr_assert_eq(blank_sequence(prev, cur), 1);
}

Test(blank_sequence, no) {
  char prev = ' ', cur = 'a';
  cr_assert_eq(blank_sequence(prev, cur), 0);

  prev = 'a', cur = 'b';
  cr_assert_eq(blank_sequence(prev, cur), 0);
}

// ####################
// counts_new
// ####################
Test(counts_new, yes) {
  Counts c = counts_new();
  cr_assert_eq(c.total_spaces, 0);
  cr_assert_eq(c.total_tabs, 0);
  cr_assert_eq(c.total_sequences, 0);
  cr_assert_eq(c.longest_sequence, 0);
  cr_assert_eq(c.total_spaces_in_longest_sequence, 0);
  cr_assert_eq(c.total_tabs_in_longest_sequence, 0);
}

// ####################
// counts_new
// ####################
Test(counts_to_str, yes) {
  Counts c = counts_new();
  c.total_spaces = 100;
  c.total_tabs = 10;
  c.total_spaces_in_longest_sequence = 25;

  char* result = counts_to_str(c);
  char* expected = "total spaces = 100\ntotal tabs = 10\ntotal sequences = 0\nlongest sequence = 0\ntotal spaces in longest sequence = 25\ntotal tabs in longest sequence = 0\n";
  cr_assert_eq(strcmp(result, expected), 0);

  free(result);
}


// ####################
// count_blanks
// ####################
Test(count_blanks, _1) {
  char str[] = "a string \t";
  Counts counts = count_blanks(str);

  cr_assert_eq(counts.total_spaces, 2);
  cr_assert_eq(counts.total_tabs, 1);
  cr_assert_eq(counts.total_sequences, 2);
  cr_assert_eq(counts.longest_sequence, 2);
  cr_assert_eq(counts.total_spaces_in_longest_sequence, 1);
  cr_assert_eq(counts.total_tabs_in_longest_sequence, 1);
}

Test(count_blanks, _2) {
  char str[] = "a string \t\t a";
  Counts counts = count_blanks(str);

  cr_assert_eq(counts.total_spaces, 3);
  cr_assert_eq(counts.total_tabs, 2);
  cr_assert_eq(counts.total_sequences, 2);
  cr_assert_eq(counts.longest_sequence, 4);
  cr_assert_eq(counts.total_spaces_in_longest_sequence, 2);
  cr_assert_eq(counts.total_tabs_in_longest_sequence, 2);
}

Test(count_blanks, _3) {
  char str[] = "\t     xxx  \t\t xx \t x";
  Counts counts = count_blanks(str);

  cr_assert_eq(counts.total_spaces, 10);
  cr_assert_eq(counts.total_tabs, 4);
  cr_assert_eq(counts.total_sequences, 3);
  cr_assert_eq(counts.longest_sequence, 6);
  cr_assert_eq(counts.total_spaces_in_longest_sequence, 5);
  cr_assert_eq(counts.total_tabs_in_longest_sequence, 1);
}
