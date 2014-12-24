import java.util.ArrayList;
import java.util.Iterator;

public class PancakeMenuAggregate implements MenuAggregate {
    MenuItem[] items;
    final int MAX_SIZE = 5;
    int position = 0;

    public PancakeMenuAggregate() {
        items = new MenuItem[MAX_SIZE];
        addItem("Blueberry cake", "cake with blue stuff", 1.23, true);
        addItem("Blackberry cake", "cake with blaue stuff", 2.23, true);
        addItem("Rooberry cake", "cake with rlue stuff", 1.43, false);
        addItem("Mooberry cake", "cake with mooue stuff", 6.23, false);
    }

    public String getName() {
        return "Pancakes";
    }

    public void addItem(String name, String description, double price, boolean isVegetarian) {
        if (position < MAX_SIZE) {
            MenuItem item = new MenuItem(name, description, price, isVegetarian);
            items[position] = item;
            position++;
        } else {
            System.out.println("Sorry the Pancake menu is full, cannot add more stuff");
        }
    }

    public Iterator createIterator() {
        return new PancakeMenuIterator(items);
    }

}
