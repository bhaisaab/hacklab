#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main() {
    while (!cin.eof()) {
        string input;
        string defender;
        cin >> input;
        cin >> defender;
        int idx = input.find("|");
        if (idx <= -1) continue;
        string left = input.substr(0, idx);
        string right = input.substr(idx+1, input.length());

        int diff = left.length() - right.length();
        if (diff == 0) {
            if (defender.length() % 2 == 0) {
                cout << left << defender.substr(0, defender.length()/2) << "|" << right << defender.substr(defender.length()/2, defender.length()) << endl;
            } else cout << "Impossible" << endl;
        } else {

            if (abs(diff) > defender.length())
                cout << "Impossible" << endl;
            else {
                if ((defender.length() - abs(diff)) > 0) {
                    if ((defender.length() - abs(diff)) % 2 != 0)
                        cout << "Impossible" << endl;
                    else {
                          int extra = defender.length() - abs(diff);
                          if (diff > 0)
                              cout << left << defender.substr(0, extra/2) << "|" << right << defender.substr(extra/2, defender.length()) << endl;
                          else
                              cout << left << defender.substr(extra/2, defender.length()) << "|" << right << defender.substr(0, extra/2) << endl;
                    }
                } else { // it's zero
                    if (diff > 0)
                        cout << left << "|" << right << defender << endl;
                    else
                        cout << defender << left << "|" << right << endl;
                }
            }
        }
    }
    return 0;
}
