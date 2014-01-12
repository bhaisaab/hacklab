/*
ID: rohitya1
LANG: C
PROG: milk2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* fin = fopen("milk2.in", "r");
    FILE* fout = fopen("milk2.out", "w");

    int n;
    int time[5000][2];

    fscanf(fin, "%d\n", &n);
    for (int i = 0; i < n; i++) //C99 loop
        fscanf(fin, "%d %d\n", &time[i][0], &time[i][1]);

    fclose(fin);
    fclose(fout);
    return 0;
}
