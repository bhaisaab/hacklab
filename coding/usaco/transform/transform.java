/*
ID: rohitya1
LANG: JAVA
PROG: transform
*/

import java.util.*;
import java.io.*;
import java.lang.*;

class Matrix {

    public int n;
    public char[][] matrix;
    public Matrix(int n) {
        this.n = n;
        this.matrix = new char[n][n];
    }

    public Matrix reflect() {
        Matrix ref = new Matrix(this.n);
        for (int i = 0; i < this.n; i++)
            for (int j = 0; j < this.n; j++)
                ref.matrix[i][j] = this.matrix[i][this.n-j-1];
        return ref;
    }

    public Matrix rotate(Matrix m) {
        Matrix rot = new Matrix(m.n);
        for (int i = 0; i < m.n; i++)
            for (int j = 0; j < m.n; j++)
                rot.matrix[j][n-1-i] = m.matrix[i][j];
        return rot;
    }

    public boolean isEqual(Matrix m) {
        if (m.n != this.n)
            return false;
        for (int i = 0; i < this.n; i++)
            for (int j = 0; j < this.n; j++)
                if (m.matrix[i][j] != this.matrix[i][j])
                    return false;
        return true;
    }
}

class transform {

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("transform.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("transform.out")));

        int n = Integer.parseInt(in.readLine());
        Matrix pattern = new Matrix(n);
        Matrix transform = new Matrix(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                pattern.matrix[i][j] = (char) in.read();
            }
            in.read(); //newline
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                transform.matrix[i][j] = (char) in.read();
            }
            in.read(); //newline
        }

        Matrix temp = pattern.rotate(pattern);
        boolean found = false;
        for (int i = 1; i <= 3; i++) {
            if (temp.isEqual(transform)) {
                out.println(i);
                found = true;
                break;
            }
            temp = temp.rotate(temp);
        }
        if (!found) {
            temp = pattern.reflect();
            if (temp.isEqual(transform)) {
                out.println("4");
                found = true;
            }
            if (!found) {
                temp = temp.rotate(temp);
                for (int i = 1; i <= 3; i++) {
                    if (temp.isEqual(transform)) {
                        out.println("5");
                        found = true;
                        break;
                    }
                    temp = temp.rotate(temp);
                }
            }
        }
        if (!found) {
            if (pattern.isEqual(transform))
                out.println("6");
            else
                out.println("7");
        }
        in.close();
        out.close();
        System.exit(0);
    }

}
