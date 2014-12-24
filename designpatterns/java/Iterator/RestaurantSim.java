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
        ArrayList menus = new ArrayList();
        menus.add(new PancakeMenuAggregate());
        menus.add(new DinerMenuAggregate());
        WaitressClient w = new WaitressClient(menus);
        w.printMenu();
    }
}
