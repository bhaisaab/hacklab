import java.util.Iterator;
import java.util.ArrayList;
import java.lang.UnsupportedOperationException;

public class WaitressClient {
    Menu menu;

    public WaitressClient (Menu menu) {
        this.menu = menu;
    }

    public void printMenu() {
        menu.print();
    }

    public void printVegMenu() {
        System.out.println("\n Vegetarian items:");
        Iterator it = new CompositeIterator(menu.createIterator());

        while (it.hasNext()) {
            MenuComponent c = (MenuComponent) it.next();
            try {
                if (c.isVegetarian()) {
                    c.print();
                }
            } catch (UnsupportedOperationException e) {}
        }
    }

}
