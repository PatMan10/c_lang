#include <stdio.h>

/*
 * Character Input and Output
 */

int main() {
  int c;

  printf("%d\n", '\b');
  while ((c = getchar()) != EOF) {
    switch(c) {
      case '\t':
        printf("\\t");
        break;

      case '\b':
        printf("\\b");
        break;

      case '\\':
        printf("\\");
        break;

      default:
        putchar(c);
        break;
    }
  }
  
  return 0;
}
