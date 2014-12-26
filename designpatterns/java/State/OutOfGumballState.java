public class OutOfGumballState implements State {
    GumballMachine m;

    public OutOfGumballState(GumballMachine m) {
        this.m = m;
    }

    public void insertCoin() {
        System.out.println("Cannot insert coin, no gumballs to sell");
    }

    public void ejectCoin() {
        System.out.println("Cannot eject coin, no gumballs to sell");
    }

    public void crank() {
        System.out.println("Sorry no gumballs");
    }

    public void dispense() {
        System.out.println("Sorry nothing to dispense, no gumballs");
    }
}
