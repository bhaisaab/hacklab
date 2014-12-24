public class PancakeMenu extends Menu {

    public PancakeMenu(String name) {
        super(name);
        add(new MenuItem("BlueBerry Chicken Pie", "Chicken flavoured pie", 1.22, false));
        add(new MenuItem("Apple Pie", "Apple flavoured pie", 2.21, true));
    }

}
