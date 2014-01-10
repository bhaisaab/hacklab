/*
ID: rohitya1
LANG: C
PROG: friday
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isleap(int year) {
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

int month_lookup[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// month1 = jan, month12 = dec
int get_days(int month, int year) {
    assert(month >= 0 && month < 12);
    if (month == 1)
        return month_lookup[month] + isleap(year);
    return month_lookup[month];
}

int main() {

    FILE *fin = fopen("friday.in", "r");
    FILE *fout = fopen("friday.out", "w");

    int n;
    int year_idx = 1900;
    int month_idx = 1; // jan = 1
    //sat = 0, sun = 1, mon = 2... friday=6
    // jan 13th 1990 was saturday or 0
    int day_idx = 0;
    int i;

    static int week[7]; // init to 0
    fscanf(fin, "%d", &n);
    fclose(fin);

    assert(n <= 400);

    for (; n > 0; --n, ++year_idx) {
        for (month_idx=0; month_idx < 12; month_idx++) {
            week[day_idx]++;
            // next 13th of the month = rest of the days + 13 (= size of current month)
            day_idx = (day_idx + get_days(month_idx, year_idx)) % 7;
        }
    }

    for (i=0; i < 7; i++) {
        fprintf(fout, "%d", week[i]);
        if (i != 6) fprintf(fout, " ");
    }
    fprintf(fout, "\n");
    fclose(fout);
    exit(0);
    return 0;
}
