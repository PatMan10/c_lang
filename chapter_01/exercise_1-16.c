#include <stdio.h>

/*
 * Print Celsius to Fahrenheit table, use function for conversion.
 */

void modify(int nums[], int size) {
   for (int i = 0; i < 10; ++i) {
    nums[i] = i * 2;
  }
}

int main() {
  int z = 10;
  int nums[z] = {};
  modify(nums, z);
  for (int i = 0; i < z; ++i) {
    printf("%d\n", nums[i]);
  } 

  char *chars = "abcde";
  // chars[1] = 'X';
  for (int i = 0; i < 5; ++i) {
    printf("%c\n", chars[i]);
  } 
}
