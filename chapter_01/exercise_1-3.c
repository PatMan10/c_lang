#include <stdio.h>

/*
 * print Fahrenheit to Celsius table
 */

int main() {
  float fahr, cels;
  int lower, upper, step;

  lower = 0; // lower limit of temprature table
  upper = 300; // upper limit
  step = 20;  // step size

  fahr = lower;
  printf("Fahrenheit to Celsius\n\n");
  while (fahr <= upper) {
    cels = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f\t%6.1f\n", fahr, cels);
    fahr = fahr + step;
  }

  return 0;
}
