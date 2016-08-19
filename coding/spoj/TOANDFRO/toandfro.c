#include <stdio.h>
#include <string.h>

int main() {
	int N;
	char str[201];
	while(1) {
		scanf("%d", &N);
		if (N == 0) {
			break;
		}
		scanf("%s", str);
		int len = strlen(str);
		for (int idx = 0; idx < N; idx++) {
			int cur = idx;
			int line = 1;
			while (cur < len) {
				printf("%c", str[cur]);
				if (line % 2 > 0) {
					cur += 2*(N-idx)-1;
				} else {
					cur += 2*idx+1;
				}
				line++;
			}
		}
		printf("\n");
	}
	return 0;
}
