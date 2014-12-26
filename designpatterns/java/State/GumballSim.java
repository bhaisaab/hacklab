public class GumballSim {
    public static void main(String[] args) {
        GumballMachine m = new GumballMachine(0);

        m.insertCoin();
        m.crank();
        m.ejectCoin();

        System.out.println(m);

        m.refill(3);

        m.insertCoin();
        m.crank();
        m.ejectCoin();

        System.out.println(m);

        m.insertCoin();
        m.insertCoin();
        m.crank();
        m.insertCoin();
        m.ejectCoin();
        m.ejectCoin();

        System.out.println(m);

        m.insertCoin();
        m.crank();
        m.ejectCoin();

        System.out.println(m);
    }
}
