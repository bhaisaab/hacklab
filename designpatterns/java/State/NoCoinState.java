public class NoCoinState implements State {
    GumballMachine m;

    public NoCoinState(GumballMachine m) {
        this.m = m;
    }

    public void insertCoin() {
        m.setState(m.getHasCoinState());
    }

    public void ejectCoin() {
        System.out.println("Sorry no coin to eject");
    }

    public void crank() {
        System.out.println("Need coin to crank");
    }

    public void dispense() {
        System.out.println("Need coin+crank to dispense");
    }
}
