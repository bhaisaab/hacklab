/*

public interface Iterator {
    public boolean hasNext();
    public Object next();
    public void remove() throws UnsupportedOperationException, IllegalStateException;
}
*/
import java.util.ArrayList;

public class RestaurantSim {
    public static void main(String[] args) {
        Menu pancake = new PancakeMenu("Pancake House");
        Menu diner = new DinerMenu("Diner");
        Menu dessert = new DessertMenu("Dessert");
        diner.add(dessert);

        Menu main = new Menu("Main Menu");
        main.add(pancake);
        main.add(diner);

        WaitressClient w = new WaitressClient(main);
        w.printMenu();
        w.printVegMenu();
    }
}
