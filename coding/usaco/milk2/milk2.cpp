/*
ID: rohitya1
LANG: C++11
PROG: milk2
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
}

int main() {
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");

    int n, start, stop;
    vector< pair<int, int> > time;
    fin >> n;
    for (int i=0; i < n; i++) {
        fin >> start >> stop;
        time.push_back(make_pair(start, stop));
    }

    sort(time.begin(), time.end(), cmp);

    start = time.at(0).first;
    stop = time.at(0).second;
    int milkTime = stop - start;
    int nonMilkTime = 0;

    for (int i = 1; i < n; i++) {
        if (time.at(i).first > stop) {
            if ((time.at(i).first - stop) > nonMilkTime)
                nonMilkTime = time.at(i).first - stop;
            start = time.at(i).first;
            stop = time.at(i).second;
        } else {
            if (time.at(i).second > stop)
                stop = time.at(i).second;
        }

        if (milkTime < (stop-start))
            milkTime = stop - start;
    }
    fout << milkTime << " " << nonMilkTime << endl;

    fin.close();
    fout.close();

    return 0;
}
