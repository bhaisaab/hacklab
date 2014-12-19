public class NYPizzaStore extends PizzaStore {
    Pizza createPizza(String type) {
        PizzaIngredientFactory idf = new NYPizzaIngredientFactory();
        Pizza p;
        switch(type) {
            case "cheese":
                p = new CheesePizza(idf);
                p.setName("NY Styled Cheese Pizza");
                break;
            case "veggie":
                p = new VeggiePizza(idf);
                p.setName("NY Styled Veggie Pizza");
                break;
            default:
                p = null;
                break;
        }
        return p;
    }
}
