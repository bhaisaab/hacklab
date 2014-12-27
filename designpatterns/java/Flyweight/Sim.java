import java.util.Random;
public class Sim {
    public static void main(String[] args) {
        String[] flavours = {"Espresso", "Latte", "Cappuchinno", "MochaFiltered"};
        Random r = new Random();
        CoffeeFlyweightFactory fac = new CoffeeFlyweightFactory();
        for (int i=0; i< 1000; i++) {
            int idx = r.nextInt(4);
            CoffeeFlyweight c = fac.getFlyweight(flavours[idx]);
            System.out.println(c);
        }
    }
}
