#include <stdio.h>
#include <math.h>

int prime[32000];

void sieve() {
	int C = 0;
	for (int i = 2; i < 32000; i++) {
		int isPrime = 1;
		for (int j = 2; j <= sqrt(i); j++) {
			if (i % j == 0) {
				isPrime = 0;
				break;
			}
		}
		if (isPrime == 1) {
			prime[C++] = i;
		}
	}
}

void print_primes(long a, long b) {
	for (long i = a; i <= b; i++) {
		if (i < 2) continue;
		int isPrime = 1;
		int val = sqrt(i);
		for (int x = 0; prime[x] <= val; x++) {
			if (i % prime[x] == 0) {
				isPrime = 0; break;
			}
		}
		if (isPrime) {
			printf("%ld\n", i);
		}
	}
}

int main() {
	int N;
	long a, b;

	sieve();
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%ld %ld", &a, &b);
		print_primes(a, b);
		if (N - i > 1) {
			printf("\n");
		}
	}
	return 0;
}
