/*
ID: rohitya1
LANG: C++11
PROG: palsquare
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stack>

using namespace std;

string convi(int i) {
    if (i < 10) return to_string(i);
    else {
        stringstream ss;
        char ch = 'A' + (char) (i - 10);
        ss << ch;
        string res;
        ss >> res;
        return res;
    }
}

string cbase(int n, int b) {
    ostringstream res;
    stack<string> rep;
    while (n > 0) {
        rep.push(convi(n%b));
        n = n / b;
    }
    while (!rep.empty()) {
        res << rep.top();
        rep.pop();
    }
    return res.str();
}

bool ispal(string& s) {
    int len = s.length();
    for (int j = 0; j < len/2; j++) {
        if (s.at(j) != s.at(len - j - 1)) return false;
    }
    return true;
}

int main() {
    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");

    int base;
    fin >> base;

    for (int i = 1; i <= 300; i++) {
        string rep = cbase(i, base);
        string srep = cbase(i*i, base);
        if (ispal(srep))
            fout << rep << " " << srep << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
