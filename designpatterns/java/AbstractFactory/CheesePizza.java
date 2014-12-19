public class CheesePizza extends Pizza {
    PizzaIngredientFactory idf;

    public CheesePizza(PizzaIngredientFactory idf) {
        this.idf = idf;
    }

    void prepare() {
        System.out.println("Preparing " + name + "...");
        dough = idf.createDough();
        sauce = idf.createSauce();
        cheese = idf.createCheese();
    }
}
