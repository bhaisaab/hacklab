public class GumballSoldState implements State {
    GumballMachine m;

    public GumballSoldState(GumballMachine m) {
        this.m = m;
    }

    public void insertCoin() {
        System.out.println("Please, wait we're already giving you a gumball");
    }

    public void ejectCoin() {
        System.out.println("Sorry, you already turned the crank");
    }

    public void crank() {
        System.out.println("Turning twice won't give you another gumball!");

    }

    public void dispense() {
        m.releaseBall();
        if (m.getGumballCount() > 0) {
            m.setState(m.getNoCoinState());
        } else {
            System.out.println("Out of Gumballs now!");
            m.setState(m.getOutOfGumballState());
        }
    }
}
