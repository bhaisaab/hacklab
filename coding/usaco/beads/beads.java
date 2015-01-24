/*
ID: rohitya1
LANG: JAVA
PROG: beads
*/

import java.util.*;
import java.io.*;
import java.lang.Math.*;


class beads {

    public static void main(String[] args) throws IOException {

        BufferedReader in = new BufferedReader(new FileReader("beads.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("beads.out")));

        int n = Integer.parseInt(in.readLine());
        String beads = in.readLine();
        beads = beads + beads; // 2 * beads string for linear traversal
        // Let's try dynamic programming
        int[][] left = new int[800][2];
        int[][] right = new int[800][2];
        left[0][0] = 0; //red
        left[0][1] = 0; //blue
        right[2*n][0] = 0;
        right[2*n][1] = 0;

        char color;
        for (int i = 1; i <= 2 * n; i++) {
            color = beads.charAt(i-1);
            if (color == 'r') {
                left[i][0] = left[i-1][0] + 1;
                left[i][1] = 0;
            } else if (color == 'b') {
                left[i][1] = left[i-1][1] + 1;
                left[i][0] = 0;
            } else {
                left[i][0] = left[i-1][0] + 1;
                left[i][1] = left[i-1][1] + 1;
            }

            int idx = 2*n - i;
            color = beads.charAt(idx);
            if (color == 'r') {
                right[idx][0] = right[idx+1][0] + 1;
                right[idx][1] = 0;
            } else if (color == 'b') {
                right[idx][1] = right[idx+1][1] + 1;
                right[idx][0] = 0;
            } else {
                right[idx][0] = right[idx+1][0] + 1;
                right[idx][1] = right[idx+1][1] + 1;
            }
        }

        int m = 0;
        for (int i = 0; i < 2*n; i++) {
            m = Math.max(m, Math.max(left[i][0], left[i][1]) + Math.max(right[i][0], right[i][1]));
        }
        out.println(Math.min(m, n));
        out.close();
        in.close();

        System.exit(0);
    }
}
