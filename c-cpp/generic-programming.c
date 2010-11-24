#include <stdio.h>
#define p(x) ({ typeof(x) p = (x); p; })
int main() { printf("generic programming: %c, %d\n", p('z'), p(10) ); }
