public class PizzaSim {
    public static void main(String[] args) {
        PizzaStore ny = new NYPizzaStore();
        PizzaStore ch = new ChicagoPizzaStore();

        ny.orderPizza("cheese");
        ny.orderPizza("veggie");

        ch.orderPizza("cheese");
        ch.orderPizza("veggie");
    }
}
