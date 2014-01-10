/*
ID: rohitya1
LANG: JAVA
TASK: friday
*/

import java.io.*;
import java.util.*;
import java.lang.*;

class friday {


    static int lookup[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    private static boolean isLeap(int year) {
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    }

    private static int days(int month, int year) {
        if (month == 1 && isLeap(year)) return lookup[month] + 1;
        return lookup[month];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("friday.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("friday.out")));

        int n = Integer.parseInt(in.readLine());
        int day = 0; //saturday, 13th jan 1900
        int[] week = new int[7];
        for (int i = 0; i < 6; i++) week[i] = 0;

        for (int year = 1900; n > 0; --n, ++year) {
            for (int month = 0; month < 12; ++month) {
                week[day]++;
                day = (day + days(month, year)) % 7;
            }
        }
        for (int i = 0; i < 7; i++) {
            out.print(week[i]);
            if (i < 6) out.print(" ");
            else out.println("");
        }
        out.close();
        System.exit(0);
    }

}
