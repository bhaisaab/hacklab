#include <stdio.h>

int main() {
    int side;
    while (1) {
        scanf("%d", &side);
        if (side < 1)
            break;
        int result = 0;
        int counter = 1;
        int n = side;
        for (;n > 0;n--) {
            result += (n*counter);
            counter += 2;
        }
        printf("%d\n", result);
    }
}
