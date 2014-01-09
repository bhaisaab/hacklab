/*
ID: rohitya1
LANG: C++11
PROG: gift1
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {

    ifstream fin ("gift1.in");
    ofstream fout ("gift1.out");

    int np;
    string person;
    int amount, division;
    vector<string> names;
    // map can lookup in logN, unordered_map can do in O(1) or max O(n)
    map<string, int> people;
    int account[10];

    fin >> np;
    for (int i = 0; i < np; i++) {
        fin >> person;
        people[person] = 0;
        names.push_back(person);
    }

    while (true) {
        fin >> person;
        if (fin.eof()) break;
        fin >> amount >> division;
        int gift = 0;
        if (division > 0) gift = amount / division;
        people[person] = people[person] + (gift * division);
        for (int i = 0; i < division; i++) {
            fin >> person;
            if (gift != 0)
                people[person] = people[person] - gift;
        }
    }
    for (auto iter = names.begin(); iter != names.end(); ++iter)
        fout << *iter << " " << -people[*iter] << endl;

    fin.close();
    fout.close();
    return 0;
}
