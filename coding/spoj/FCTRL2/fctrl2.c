#include <stdio.h>

unsigned long long fac(int a) {
	if (a < 2) return 1;
	unsigned long long val = 1LL;
	for (int i = 2; i <= a; i++) {
		val *= i;
	}
	return val;
}

int main() {
	int N;
	int a;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &a);
		printf("%llu\n", fac(a));
	}
	return 0;
}
