#include "lib.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

// STR_LEN
Test(str_len, pass) {
  int result = str_len("");
  cr_assert_eq(result, 0);

  result = str_len("a");
  cr_assert_eq(result, 1);

  result = str_len("abc");
  cr_assert_eq(result, 3);
}

// SPACE
Test(space, yes) {
  char c = ' ';
  cr_assert_eq(space(c), 1);
}

Test(space, no) {
  char c = '\t';
  cr_assert_eq(space(c), 0);
}

// TAB
Test(tab, yes) {
  char c = '\t';
  cr_assert_eq(tab(c), 1);
}

Test(tab, no) {
  char c = ' ';
  cr_assert_eq(tab(c), 0);
}

// BLANK
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


// BLANK_SEQ
Test(blank_seq, yes) {
  char prev = 'a', cur = ' ';
  cr_assert_eq(blank_seq(prev, cur), 1);

  prev = '\t', cur = ' ';
  cr_assert_eq(blank_seq(prev, cur), 1);
}

Test(blank_seq, no) {
  char prev = ' ', cur = 'a';
  cr_assert_eq(blank_seq(prev, cur), 0);

  prev = 'a', cur = 'b';
  cr_assert_eq(blank_seq(prev, cur), 0);
}
