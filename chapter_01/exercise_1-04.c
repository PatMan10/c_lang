#include <stdio.h>

/*
 * print Celsius to Fahrenheit table
 */

int main() {
  float fahr, cels;
  float lower = -17.8,   // lower limit of temprature table
      upper = 148.9, // upper limit
      step  = 11.1;  // step size


  cels = lower;
  printf("Celsius to Fahrenheit\n\n");
  while (cels <= upper) {
    fahr = (cels * 1.8) + 32.0;
    printf("%6.1f\t%3.1f\n", cels, fahr);
    cels = cels + step;
  }

  return 0;
}
