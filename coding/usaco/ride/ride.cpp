/*
ID: rohitya1
LANG: C++11
PROG: ride
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    ifstream fin ("ride.in");
    ofstream fout ("ride.out");

    string comet;
    string group;
    int comet_num = 1;
    int group_num = 1;
    fin >> comet >> group;

    // C++98
    for(string::const_iterator i = comet.begin(); i!=comet.end(); i++)
        comet_num = comet_num * (char(*i) - 'A' + 1);
    comet_num = comet_num % 47;

    // C++11
    for(char& c: group)
        group_num = group_num * (c - 'A' + 1);
    group_num = group_num % 47;

    if (comet_num == group_num)
        fout << "GO" << endl;
    else
        fout << "STAY" << endl;

    return 0;
}
