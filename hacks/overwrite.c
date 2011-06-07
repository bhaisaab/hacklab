#include <stdio.h>

void f()
{
    char a;
    * (char **) (&a + 9) += 20;
}

int main()
{
    printf("1\n");
    f();
    printf("2\n");
    printf("3\n");
    return 0;
}
