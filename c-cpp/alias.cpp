#include <stdio.h>
main()
{
  int i = 10;
  int &j = i;
  printf("i(%p) = %d; j(%p) = %d\n", &i, i, &j, j);
}
