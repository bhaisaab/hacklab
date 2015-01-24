/*
ID: rohitya1
LANG: JAVA
TASK: ride
*/

import java.io.*;
import java.util.*;


class ride {
    public static void main(String args[]) throws IOException {
        BufferedReader f = new BufferedReader(new FileReader("ride.in"));

        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ride.out")));

        int comet_num = 1;
        int group_num = 1;
        String comet = f.readLine();
        String group = f.readLine();

        for(char ch: comet.toCharArray())
            comet_num = comet_num * (ch - 'A' + 1);
        comet_num = comet_num % 47;

        for(int i = 0; i < group.length(); i++)
            group_num = group_num * (group.charAt(i) - 'A' + 1);
        group_num = group_num % 47;

        if (comet_num == group_num)
            out.println("GO");
        else
            out.println("STAY");
        out.close();
        System.exit(0);
    }
}
