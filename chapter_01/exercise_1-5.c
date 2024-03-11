#include <stdio.h>

/*
 * print Fahrenheit to Celsius table
 */

#define LOWER 0
#define UPPER 300
#define STEP 20

int main() {
  printf("Fahrenheit to Celsius\n\n");
  for (float fahr = LOWER; fahr <= UPPER; fahr += STEP) {
    float cels = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f\t%6.1f\n", fahr, cels);
  }

  return 0;
}
