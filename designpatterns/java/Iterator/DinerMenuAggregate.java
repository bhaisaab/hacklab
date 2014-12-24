import java.util.ArrayList;
import java.util.Iterator;

public class DinerMenuAggregate implements MenuAggregate {
    ArrayList items;
    public DinerMenuAggregate() {
        items = new ArrayList();
        addItem("Samosa", "cake with blue stuff", 10.23, true);
        addItem("Kachori", "cake with blaue stuff", 11.23, true);
        addItem("Bhel", "cake with rlue stuff", 19.43, true);
        addItem("Aaloo chicken chat", "cake with mooue stuff", 26.23, false);
    }

    @SuppressWarnings("unchecked")
    public void addItem(String name, String description, double price, boolean isVegetarian) {
        MenuItem item = new MenuItem(name, description, price, isVegetarian);
        items.add((Object)item);
    }

    public String getName() {
        return "Main course Diner";
    }

    public Iterator createIterator() {
        return items.iterator();
    }

}
