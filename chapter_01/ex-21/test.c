#include "lib.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(str_len, passing) {
  int result = str_len("abc");
  cr_assert_eq(result, 3);
}
