public class ChicagoPizzaStore extends PizzaStore {
    Pizza createPizza(String type) {
        PizzaIngredientFactory idf = new ChicagoPizzaIngredientFactory();
        Pizza p;
        switch(type) {
            case "cheese":
                p = new CheesePizza(idf);
                p.setName("Chicago Styled Cheese Pizza");
                break;
            case "veggie":
                p = new VeggiePizza(idf);
                p.setName("Chicago Styled Veggie Pizza");
                break;
            default:
                p = null;
                break;
        }
        return p;
    }
}
