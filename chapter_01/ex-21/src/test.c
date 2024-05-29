#include <stdio.h>
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
// blank_sequence
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
// count_blanks
// ####################
Test(count_blanks, _1) {
  char str[] = "a string \t";
  int counts[] = {0,0,0,0,0};

  count_blanks(str, counts);
  cr_assert_eq(counts[0], 2);
  cr_assert_eq(counts[1], 1);
  cr_assert_eq(counts[2], 2);
  cr_assert_eq(counts[3], 1);
  cr_assert_eq(counts[4], 1);
}

Test(count_blanks, _2) {
  char str[] = "a string \t\t a";
  int counts[] = {0,0,0,0,0};

  count_blanks(str, counts);
  cr_assert_eq(counts[0], 3);
  cr_assert_eq(counts[1], 2);
  cr_assert_eq(counts[2], 4);
  cr_assert_eq(counts[3], 2);
  cr_assert_eq(counts[4], 2);
}

Test(count_blanks, _3) {
  char str[] = "\t     xxx  \t\t xx \t x";
  int counts[] = {0,0,0,0,0};

  count_blanks(str, counts);
  cr_assert_eq(counts[0], 10);
  cr_assert_eq(counts[1], 4);
  cr_assert_eq(counts[2], 6);
  cr_assert_eq(counts[3], 5);
  cr_assert_eq(counts[4], 1);
}
