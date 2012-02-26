#include <stdio.h>
int main(int argc, char **argv) {
  int b;
  int a;
  for (a = 0; a < 5; a++) {
    asm("cpuid"
      : "=a" (b)   /* EAX into b (output) */
      : "a"  (a)); /* a into EAX (input)  */

    printf("The code %d gives %d\n", a, b);
  }
}
