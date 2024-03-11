#include <stdio.h>

/*
 * print Fahrenheit to Celsius table
 */

int main() {
  printf("Fahrenheit to Celsius\n\n");
  for (float fahr = 0; fahr <= 300; fahr += 20) {
    float cels = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f\t%6.1f\n", fahr, cels);
  }

  return 0;
}
