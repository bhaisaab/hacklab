#include <stdio.h>

int rev(int x) {
	int r = 0;
	while (x > 0) {
		r = 10*r + (x%10);
		x/= 10;
	}
	return r;
}

int main() {
	int N;
	int a, b;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &a, &b);
		printf("%d\n", rev(rev(a) + rev(b)));
	}
	return 0;
}
