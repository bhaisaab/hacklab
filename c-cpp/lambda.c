#include <stdio.h>
#define lambda(return_type, body_and_args) \
  ({ \
    return_type __fn__ body_and_args \
    __fn__; \
  })
main()
{
  int (*max)(int, int) = lambda (int , (int x, int y) { return x > y ? x : y; }); 
  printf("Max(10, 20) = %d\n", max(10,20));
}
