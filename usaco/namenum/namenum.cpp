/*
ID: rohitya1
LANG: C++11
PROG: namenum
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
    ifstream fin("namenum.in");
    ifstream dictin("dict.txt");
    ofstream fout("namenum.out");

    string brand;
    fin >> brand;

    map<char, char> lookup;
    multimap<string, string> dict;

    lookup['A'] = lookup['B'] = lookup['C'] = '2';
    lookup['D'] = lookup['E'] = lookup['F'] = '3';
    lookup['G'] = lookup['H'] = lookup['I'] = '4';
    lookup['J'] = lookup['K'] = lookup['L'] = '5';
    lookup['M'] = lookup['N'] = lookup['O'] = '6';
    lookup['P'] = lookup['R'] = lookup['S'] = '7';
    lookup['T'] = lookup['U'] = lookup['V'] = '8';
    lookup['W'] = lookup['X'] = lookup['Y'] = '9';

    string word;
    while (!dictin.eof()) {
        dictin >> word;
        bool pass = false;
        string key = "";
        for (int i = 0; i < word.length(); i++) {
            char ch = word.at(i);
            if (ch == 'Z' || ch == 'Q') { pass = true; break;}
            key += lookup[ch];
        }
        if (!pass) {
            dict.insert(pair<string, string>(key, word));
        }
    }
    dictin.close();

    auto range = dict.equal_range(string(brand));
    int result = 0;
    for (auto it = range.first; it != range.second; it++) {
        fout << it->second << endl;
        result++;
    }
    if (result == 0) fout << "NONE" << endl;

    fin.close();
    fout.close();
    return 0;
}
