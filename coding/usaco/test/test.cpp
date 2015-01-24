/*
ID: rohitya1
LANG: C++
TASK: test
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    ifstream fin ("test.in");
    ofstream fout ("test.out");

    int a, b;
    fin >> a >> b;
    fout << a+b << endl;

    return 0;
}
