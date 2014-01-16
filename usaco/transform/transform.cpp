/*
ID: rohitya1
LANG: C++11
PROG: transform
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct matrix {
    char matrix[10][10];
    int n;
};

void print_matrix(matrix& tmp) {
    int n = tmp.n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << tmp.matrix[i][j] << " ";
        cout << endl;
    }
}

bool match(matrix& src, matrix& dst) {
    int n = src.n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (src.matrix[i][j] != dst.matrix[i][j])
                return false;
    return true;
}

matrix reflect(matrix &src) {
    int n = src.n;
    matrix transform;
    transform.n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transform.matrix[i][j] = src.matrix[i][n-j-1];
        }
    }
    return transform;
}

// rotates src by 90"
matrix rotate(matrix& src) {
    int n = src.n;
    matrix transform;
    transform.n = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            transform.matrix[j][n-1-i] = src.matrix[i][j];
    return transform;
}

//clockwise rotate src, dst
int check_rotate(matrix& src, matrix& dst) {
    int result = 1;
    int rot = 270;
    matrix tmp = src;
    while (rot > 0) {
        rot -= 90;
        tmp = rotate(tmp);
        if (match(tmp, dst))
            return result;
        result++;
    }
    return 0;
}

int main() {
    ifstream fin ("transform.in");
    ofstream fout ("transform.out");

    int n, t;
    char newline;
    matrix pattern;
    matrix transform;

    fin >> n;
    pattern.n = n;
    transform.n = n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
          fin >> pattern.matrix[i][j];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
          fin >> transform.matrix[i][j];
    }

    t = check_rotate(pattern, transform);
    if (t != 0)
        fout << t << endl;
    else {
      matrix ref = reflect(pattern);
      if(match(ref, transform))
          fout << 4 << endl;
      else {
        t = check_rotate(ref, transform);
        if (t!=0)
            fout << 5 << endl;
        else
            if (match(pattern, transform))
                fout << 6 << endl;
            else
                fout << 7 << endl;
      }

    }

    fin.close();
    fout.close();
    return 0;
}
