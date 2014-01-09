/*
ID: rohitya1
LANG: JAVA
TASK: gift1
*/

import java.io.*;
import java.util.*;
import java.lang.*;


class gift1 {
    public static void main(String args[]) throws IOException {
        BufferedReader f = new BufferedReader(new FileReader("gift1.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("gift1.out")));

        int np = Integer.parseInt(f.readLine());
        Map<String, Integer> people = new HashMap<String, Integer>();
        List<String> names = new ArrayList<String>();
        String person;

        for (int i = 0; i < np; i++) {
            person = f.readLine();
            people.put(person, new Integer(0));
            names.add(person);
        }

        while((person = f.readLine()) != null && person.length() != 0) {
            StringTokenizer st = new StringTokenizer(f.readLine(), " ");
            int amount = Integer.parseInt(st.nextToken());
            int division = Integer.parseInt(st.nextToken());
            int gift = 0;
            if (division > 0) {
                gift = (amount - (amount % division)) / division;
            }
            int value = people.get(person).intValue();
            people.put(person, new Integer(value + (gift * division)));
            for (; division > 0; --division) {
                person = f.readLine();
                value = people.get(person).intValue();
                people.put(person, new Integer(value - gift));
            }
        }

        for(String name: names) {
            out.println(name + " " + -people.get(name).intValue());
        }

        out.close();
        System.exit(0);
    }
}
