#include <stdio.h>

void f()
{
    char a;
    // on 32 bit systems, 4(size of %ebp)+1(size of char) += 0xc
    * (char **) (&a + 9) += 10;
}

int main()
{
    printf("1\n");
    f();
    printf("2\n");
    printf("3\n");
    return 0;
}
