/*
ID: rohitya1
LANG: C
PROG: beads
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mod (int a, int b) {
    return (a % b + b) % b;
}

int main() {
    FILE *fin = fopen("beads.in", "r");
    FILE *fout = fopen("beads.out", "w");

    int n;
    char beads[351];
    int idx, count;
    int max_beads = 0;
    int left_idx, right_idx;
    char left, right;

    fscanf(fin, "%d\n", &n);
    for (idx = 0; idx < n; idx++) fscanf(fin, "%c", &beads[idx]);

    for (idx = 0; idx < n; idx++) {
        right_idx = idx;
        left_idx = idx-1;
        right = beads[right_idx];
        left = beads[mod(left_idx, n)];

        count = 0;
        // count right
        for (; (beads[right_idx % n] == right || beads[right_idx % n] == 'w') && right_idx < (n+idx); right_idx++) count++;
        if (right == 'w') {
            right = beads[right_idx % n];
            for (; (beads[right_idx % n] == right || beads[right_idx % n] == 'w') && right_idx < (n+idx); right_idx++) count++;
        }

        // count left
        for (; (beads[mod(left_idx, n)] == left || beads[mod(left_idx, n)] == 'w') && left_idx >= -(n-idx) ; left_idx--) count++;
        if (left == 'w') {
            left = beads[mod(left_idx, n)];
            for (; (beads[mod(left_idx, n)] == left || beads[mod(left_idx, n)] == 'w') && left_idx >= -(n-idx) ; left_idx--) count++;
        }

        if (count > max_beads) max_beads = count;
        // possible all same colors
        if (max_beads >= n) {
            max_beads = n;
            break;
        }
    }

    fprintf(fout, "%d\n", max_beads);
    fclose(fin);
    fclose(fout);
    exit(0);
    return 0;
}

