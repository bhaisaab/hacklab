#include <stdio.h>
main()
{
  int num;
  while( scanf("%d", &num) != EOF )
  {
    if( num == 42)
      return 0;
    printf("%d\n", num);
  }
}
