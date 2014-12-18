public class CoffeeSim {

    public static void printBeverage(Beverage b) {
        System.out.printf("%s $%.2f\n", b.getDescription(), b.cost());
    }

    public static void main(String[] args) {
        Beverage b1 = new Espresso();
        printBeverage(b1);

        Beverage b2 = new Decaf();
        b2 = new Mocha(b2);
        b2 = new Milk(b2);
        b2 = new Whip(b2);
        b2 = new Whip(b2);
        printBeverage(b2);

        Beverage b3 = new Espresso();
        b3 = new Soy(b3);
        b3 = new Whip(b3);
        printBeverage(b3);
    }
}
