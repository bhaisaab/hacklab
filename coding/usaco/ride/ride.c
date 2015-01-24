/*
ID: rohitya1
LANG: C
PROG: ride
*/

#include <stdio.h>
#include <stdlib.h>

int translate(char c) {
    return (int)(c - 'A') + 1;
}

main() {

    FILE *fin = fopen("ride.in", "r");
    FILE *fout = fopen("ride.out", "w");

    char comet[7];
    char group[7];
    int i;
    int comet_num = 1;
    int group_num = 1;

    fscanf(fin, "%s\n", comet);
    fscanf(fin, "%s\n", group);

    for(i=0; comet[i] != '\0'; i++) {
        comet_num = comet_num * translate(comet[i]);
        comet_num = comet_num % 47;
    }

    for(i=0; group[i] != '\0'; i++) {
        group_num = group_num * translate(group[i]);
        group_num = group_num % 47;
    }

    if (group_num == comet_num)
        fprintf(fout, "GO\n");
    else
        fprintf(fout, "STAY\n");
    exit(0);
}
