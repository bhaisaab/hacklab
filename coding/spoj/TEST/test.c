#include <stdio.h>

int main(void) {
	int i;
	while(scanf("%d", &i) != EOF) {
		if (i == 42) {
			break;
		}
		printf("%d\n", i);
	}
	return 0;
}
