public class DinerMenu extends Menu {

    public DinerMenu(String name) {
        super(name);
        add(new MenuItem("Chicken tikka", "Chicken tikka masala", 11.22, false));
        add(new MenuItem("Paneer tikka", "Paneer tikka", 12.21, true));
        add(new MenuItem("Gobi tikka", "Veg kofta tikka", 10.21, true));
    }

}
