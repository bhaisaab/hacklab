import java.util.ArrayList;

public abstract class Pizza {
    String name;
    Dough dough;
    Sauce sauce;
    Veggies veggies[];
    Cheese cheese;

    abstract void prepare();

    void bake() {
        System.out.println("Bake for 25 mins at 350");
    }

    void cut() {
        System.out.println("Cutting pizza into diagonal slices");
    }

    void box() {
        System.out.println("Placing pizza in box");
    }

    void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public String toString() {
        String repr = "Pizza :: " + dough.toString() + " " + sauce.toString() + " ";
        if (cheese != null)
            repr += cheese.toString();
        if (veggies != null) {
            repr += " with ";
            for (int i = 0; i < veggies.length; i++) {
                repr = repr + veggies[i].toString() + " ";
            }
        }
        return repr;
    }
}
