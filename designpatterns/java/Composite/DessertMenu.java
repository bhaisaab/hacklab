public class DessertMenu extends Menu {

    public DessertMenu(String name) {
        super(name);
        add(new MenuItem("Pan iceream", "Pan ice-cream", 2.21, true));
        add(new MenuItem("Kulfi", "Kufli", 1.89, true));
    }

}
