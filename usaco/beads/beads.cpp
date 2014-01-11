/*
ID: rohitya1
LANG: C++11
PROG: beads
*/

#include <fstream>
#include <iostream>

using namespace std;

int mod(int a, int b) {
    return (a % b + b) % b;
}

int main() {
    ifstream fin("beads.in");
    ofstream fout("beads.out");

    int n;
    char beads[350];
    int max = 0;
    int count;
    int idx;
    char color;

    fin >> n;
    fin >> beads;

    for (int i = 0; i < n; i++) {
        count = 0;
        // count right
        idx = i;
        color = beads[idx];
        for (; (beads[mod(idx, n)] == color || beads[mod(idx, n)] == 'w') && idx < (i+n); ++idx) ++count;
        if (color == 'w') {
            color = beads[mod(idx, n)];
            for (; (beads[mod(idx, n)] == color || beads[mod(idx, n)] == 'w') && idx < (i+n); ++idx) ++count;
        }

        // count left
        idx = i-1;
        color = beads[mod(idx, n)];
        for (; (beads[mod(idx, n)] == color || beads[mod(idx,n)] == 'w') && idx >= -(n-i); --idx) ++count;
        if (color == 'w') {
            color = beads[mod(idx, n)];
            for (; (beads[mod(idx, n)] == color || beads[mod(idx,n)] == 'w') && idx >= -(n-i); --idx) ++count;
        }

        if (count > max) max = count;
        if (max >= n) {
            max = n;
            break;
        }
    }
    fout << max << endl;

    fin.close();
    fout.close();
    return 0;
}
