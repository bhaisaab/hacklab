public class ChicagoPizzaFactory extends AbstractPizzaFactory {
    Pizza createPizza(String type) {
        Pizza p;
        switch(type) {
            case "cheese":
                p = new ChicagoStyleCheesePizza();
                break;
            case "veggie":
                p = new ChicagoStyleVeggiePizza();
                break;
            default:
                p = null;
                break;
        }
        return p;
    }
}
