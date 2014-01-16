/*
ID: rohitya1
LANG: JAVA
PROG: namenum
*/

import java.util.*;
import java.io.*;
import java.lang.*;

class namenum {

    private static char lookup(char ch) {
        switch(ch) {
            case 'A': case 'B': case 'C': return '2';
            case 'D': case 'E': case 'F': return '3';
            case 'G': case 'H': case 'I': return '4';
            case 'J': case 'K': case 'L': return '5';
            case 'M': case 'N': case 'O': return '6';
            case 'P': case 'R': case 'S': return '7';
            case 'T': case 'U': case 'V': return '8';
            case 'W': case 'X': case 'Y': return '9';
        }
        return '0';
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("namenum.in"));
        BufferedReader dictin = new BufferedReader(new FileReader("dict.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("namenum.out")));

        String brand = in.readLine();
        int results = 0;
        String word;
        while ((word = dictin.readLine()) != null) {
            String key = "";
            boolean pass = false;
            for(char ch: word.toCharArray()) {
                if (ch == 'Z' || ch == 'Q') {
                    pass = true; break;
                }
                key += namenum.lookup(ch);
            }
            if (!pass && key.equals(brand)) {
                results++;
                out.println(word);
            }
        }
        if (results == 0) out.println("NONE");

        in.close();
        out.close();
        dictin.close();
        System.exit(0);
    }
}
