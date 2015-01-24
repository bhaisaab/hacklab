/*
ID: rohitya1
LANG: JAVA
PROG: milk2
*/

import java.util.*;
import java.lang.*;
import java.io.*;

class event {
    public int time; // time after 5H
    public boolean status; //start = true, stop = falsea
    public event(int time, boolean status) {
        this.time = time;
        this.status = status;
    }
}

class milk2 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("milk2.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("milk2.out")));

        int n = Integer.parseInt(in.readLine());
        List<event> events = new ArrayList<event>();

        for (int i = 0; i < n; i++) {
            StringTokenizer ss = new StringTokenizer(in.readLine());
            events.add(new event(Integer.parseInt(ss.nextToken()), true));
            events.add(new event(Integer.parseInt(ss.nextToken()), false));
        }

        Comparator<event> cmp = new Comparator<event>(){
            public int compare(event a, event b) {
                return Integer.valueOf(a.time).compareTo(Integer.valueOf(b.time));
            }
        };

        Collections.sort(events, cmp);

        int milkers = 0;
        int milkTime = 0;
        int nonMilkTime = 0;
        int start = events.get(0).time;
        int last = start;
        boolean noneBefore = false;

        for (event e: events) {
            if (e.status) milkers++;
            else milkers--;

            if (milkers == 1 && noneBefore && (e.time != last)) {
                start = e.time;
                int length = e.time - last;
                if (length > nonMilkTime) nonMilkTime = length;
            }

            if (milkers == 0) {
                int length = e.time - start;
                if (length > milkTime) milkTime = length;
            }

            if (milkers == 0) noneBefore = true;
            else noneBefore = false;

            last = e.time;
        }

        out.printf("%d %d\n", milkTime, nonMilkTime);

        in.close();
        out.close();

        System.exit(0);
    }
}
