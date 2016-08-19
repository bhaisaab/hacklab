#include <stdio.h>

int zeroes(long nfac) {
	int count = 0;
	long div = 5;
	while (nfac / div > 0) {
		count += nfac/div;
		div *= 5;
	}
	return count;
}

int main() {
	int N;
	long n;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%ld", &n);
		printf("%d\n", zeroes(n));
	}
}
