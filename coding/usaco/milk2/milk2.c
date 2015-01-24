/*
ID: rohitya1
LANG: C
PROG: milk2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// took 40 mins to think, need to improve timings
int main() {
    FILE* fin = fopen("milk2.in", "r");
    FILE* fout = fopen("milk2.out", "w");

    int n;
    int time[5000][2];
    int minTime = 0;
    int maxTime = 0;
    int milkTime = 0;
    int nonMilkTime = 0;
    int i, j, start, stop;

    fscanf(fin, "%d\n", &n);
    for (i = 0; i < n; i++) //C99 loop
        fscanf(fin, "%d %d\n", &time[i][0], &time[i][1]);

    //sort time by time[0]
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (time[j][0] < time[i][0]) {
                start = time[i][0];
                stop = time[i][1];
                // swap i and j
                time[i][0] = time[j][0];
                time[i][1] = time[j][1];

                time[j][0] = start;
                time[j][1] = stop;
            }
        }
    }

    minTime = time[0][0];
    maxTime = time[0][1];
    milkTime = maxTime - minTime;
    nonMilkTime = 0;
    for (i = 1; i < n; i++) {
        // no overlap
        if (time[i][0] > maxTime) {
            minTime = time[i][0];
            if ((time[i][0]-maxTime) > nonMilkTime)
                nonMilkTime = (time[i][0] - maxTime);
            maxTime = time[i][1];
        } else {
            if (time[i][1] > maxTime) {
                maxTime = time[i][1];
            }
        }
        if ((maxTime - minTime) > milkTime)
            milkTime = maxTime - minTime;
    }

    fprintf(fout, "%d %d\n", milkTime, nonMilkTime);

    fclose(fin);
    fclose(fout);
    return 0;
}
