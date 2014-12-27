import java.util.List;
import java.util.ArrayList;

public class Vacation {

    List<Event> vacation = new ArrayList<Event>();
    public void add(Event e) {
        vacation.add(e);
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        for (Event e: vacation) {
            s.append("Day=" + e.getDay() + " : " + e.getName() + "\n");
        }
        return s.toString();
    }
}
