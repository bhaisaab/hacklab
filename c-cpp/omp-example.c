/* Runs for loop statements in OpenMP supported flow */
#include <stdio.h>
main()
{
  int i, a[3];
  #pragma omp parallel for
  for(i = 0;  i < 3; i++ ) {
    a[i] = i*i;
  }
  printf("Values: %d, %d, %d\n", a[0], a[1], a[2]);
}
