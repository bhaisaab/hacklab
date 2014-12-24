import java.util.ArrayList;
import java.util.Iterator;

public class Menu extends MenuComponent {
    String name;
    ArrayList items = new ArrayList();

    public Menu(String name) {
        this.name = name;
    }

    public void add(MenuComponent m) {
        items.add(m);
    }

    public void remove(MenuComponent m) {
        items.remove(m);
    }

    public MenuComponent getChild(int i) {
        return (MenuComponent) items.get(i);
    }

    public Iterator createIterator() {
        return items.iterator(); //new CompositeIterator(items.iterator());
    }

    public void print() {
        System.out.println("\n##MENU: " + name);
        Iterator it = items.iterator();
        while (it.hasNext()) {
            MenuComponent m = (MenuComponent) it.next();
            m.print();
        }
    }
}
