public class NYPizzaFactory extends AbstractPizzaFactory {
    Pizza createPizza(String type) {
        Pizza p;
        switch(type) {
            case "cheese":
                p = new NYStyleCheesePizza();
                break;
            case "veggie":
                p = new NYStyleVeggiePizza();
                break;
            default:
                p = null;
                break;
        }
        return p;
    }
}
