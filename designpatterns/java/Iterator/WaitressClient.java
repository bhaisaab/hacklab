import java.util.Iterator;
import java.util.ArrayList;

public class WaitressClient {

    ArrayList menus;

    public WaitressClient (ArrayList menus) {
        this.menus = menus;
    }

    public void printMenu() {
        for (Object item:  menus) {
            MenuAggregate menu = (MenuAggregate) item;
            Iterator it = menu.createIterator();
            System.out.println("MENU: " + menu.getName());
            printMenu(it);
            System.out.println("\n");
        }
    }

    public void printMenu(Iterator it) {
        while (it.hasNext()) {
            MenuItem item = (MenuItem) it.next();
            System.out.println("Name = " + item.getName());
            System.out.println("Des = " + item.getDescription());
            System.out.println("Price = " + item.getPrice());
            System.out.println("Vege = " + item.isVegetarian());
            System.out.println("");
        }
    }
}
