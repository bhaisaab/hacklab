#include <stdio.h>
#include <math.h>
#include <string.h>

int plen = 0;
int prime[50000];
char primenow[1000001];

void sieve() {
	for (int i = 2; i < 50000; i++) {
		int isPrime = 1;
		int search = sqrt(i);
		for (int x = 0; x < plen; x++) {
			if (prime[x] > search) break;
			if (i % prime[x] == 0) {
				isPrime = 0;
				break;
			}
		}
		if (isPrime == 1) {
			prime[plen++] = i;
		}
	}
}

void print_primes(long a, long b) {
	memset(&primenow, 1, sizeof(primenow));
	for (int i = 0; i < plen; i++) {
		long p = prime[i];
		if (p > b) break;
		long s = a / p;
		for (long z = p*s; z <= b; z += p) {
			if (z < a) continue;
			primenow[z-a] = 0;
		} 
	}
	if (a == 1) primenow[0] = 0;
	for (int i = 0; i < plen; i++) {
		long p = prime[i];
		if (p >= a && p <= b) {
			primenow[p-a] = 1;
		}
	}
	for (int i = 0; i <= (b-a); i++) {
		if (primenow[i] == 1) {
			printf("%ld\n", a+i);
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
	}
	return 0;
}
