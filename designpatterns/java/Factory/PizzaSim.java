public class PizzaSim {
    public static void main(String[] args) {
        AbstractPizzaFactory nyFactory = new NYPizzaFactory();
        AbstractPizzaFactory chicagoFactory = new ChicagoPizzaFactory();

        Pizza pizza = nyFactory.orderPizza("cheese");
        System.out.println("Mamu ordered a " + pizza.getName() + "\n");

        pizza = chicagoFactory.orderPizza("cheese");
        System.out.println("Ramu ordered a " + pizza.getName() + "\n");

        pizza = chicagoFactory.orderPizza("veggie");
        System.out.println("Bamu ordered a " + pizza.getName() + "\n");
    }
}
