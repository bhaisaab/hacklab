import java.util.ArrayList;

public abstract class Pizza {
    String name;
    String dough;
    String sauce;
    ArrayList<String> toppings = new ArrayList<String>();

    void prepare() {
        System.out.println("Preparing " + name);
        System.out.println("Tossing dough " + dough);
        System.out.println("Adding sauce " + sauce);
        for (int i = 0; i < toppings.size(); i++) {
            System.out.println("Adding topping " + toppings.get(i));
        }
    }

    void bake() {
        System.out.println("Bake for 25 mins at 350");
    }

    void cut() {
        System.out.println("Cutting pizza into diagonal slices");
    }

    void box() {
        System.out.println("Placing pizza in box");
    }

    public String getName() {
        return name;
    }
}
