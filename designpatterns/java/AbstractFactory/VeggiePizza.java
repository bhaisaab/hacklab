public class VeggiePizza extends Pizza {
    PizzaIngredientFactory idf;

    public VeggiePizza(PizzaIngredientFactory idf) {
        this.idf = idf;
    }

    void prepare() {
        System.out.println("Preparing " + name + "...");
        dough = idf.createDough();
        sauce = idf.createSauce();
        veggies = idf.createVeggies();
    }
}
