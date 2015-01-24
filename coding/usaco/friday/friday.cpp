/*
ID: rohitya1
LANG: C++11
PROG: friday
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int lookup[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isleap(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int monthLength(int month, int year) {
    if (month == 1) return lookup[month] + isleap(year);
    return lookup[month];
}

int main() {

    ifstream fin ("friday.in");
    ofstream fout ("friday.out");

    int n;
    static int week[7];
    // 13th jan 1990 was saturday
    int day = 0;

    fin >> n;
    fin.close();

    for (int year = 1900; n > 0; --n, ++year) {
        for (int month = 0; month < 12; month++) {
            week[day]++;
            day = (monthLength(month, year) + day) % 7;
        }
    }
    for (int i = 0; i < 7; i++) {
        fout << week[i];
        if (i < 6) fout << " ";
    }
    fout << endl;

    fout.close();
    return 0;
}
