/*
ID: rohitya1
LANG: C
PROG: gift1
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lookup(char giver[15], char people[10][15], int np) {
    int idx = -1;
    int i = 0;
    for (; i < np; i++) {
        if (strcmp(giver, people[i]) == 0) {
            idx = i;
            break;
        } else idx = -1;
    }
    assert(idx != -1);
    return idx;
}


main() {

    FILE *fin = fopen("gift1.in", "r");
    FILE *fout = fopen("gift1.out", "w");

    int np;
    int i;

    int account[10];
    char people[10][15];
    char person[15];
    int amount;
    int division;
    int gift;
    int idx;

    fscanf(fin, "%d\n", &np);
    for (i=0; i < np; i++) {
        fscanf(fin, "%s\n", &people[i]);
        account[i] = 0;
    }

    while (fscanf(fin, "%s\n", &person) != EOF) {
        fscanf(fin, "%d %d\n", &amount, &division);

        if (division > 0) // do what?
            gift = amount / division;
        else
            gift = 0;

        idx = lookup(person, people, np);
        account[idx] = account[idx] + (gift * division);
        for (; division > 0; --division ) {
            fscanf(fin, "%s\n", &person);
            if (gift == 0) continue;
            idx = lookup(person, people, np);
            account[idx] = account[idx] - gift;
        }
    }
    for (i = 0; i < np; i++) {
        fprintf(fout, "%s %d\n", people[i], -account[i]);
    }

    fclose(fin);
    fclose(fout);
    exit(0);
}
