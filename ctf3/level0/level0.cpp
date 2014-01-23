#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

int main(int argc, char** argv) {
    string path = "/usr/share/dict/words";
    if (argc > 1)
        path = argv[1];

    unordered_set<string> entries;
    ifstream fin(path);
    string line;

    while (getline(fin, line)) {
        if (fin.eof()) break;
        entries.insert(line);
    }

    while (getline(cin, line)) {
        if (cin.eof()) break;
        queue<char> shaker;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] != ' ')
                shaker.push(line[i]);
            if (line[i] == ' ' || (i == line.length()-1)) {
                string word = "";
                while (!shaker.empty()) {
                    word += shaker.front();
                    shaker.pop();
                }
                string word_lower;
                word_lower.resize(word.size());
                transform(word.begin(), word.end(), word_lower.begin(), ::tolower);
                if (entries.count(word_lower) > 0) cout << word;
                else cout << "<" << word << ">";
                if (line.at(i) == ' ') cout << " ";
            }
        }
        cout << endl;
    }

    fin.close();
    return 0;
}
