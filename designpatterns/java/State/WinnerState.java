public class WinnerState implements State {
    GumballMachine m;

    public WinnerState(GumballMachine m) {
        this.m = m;
    }

    public void insertCoin() {
        System.out.println("Already have coin");
    }

    public void ejectCoin() {
        System.out.println("Coin returned");
        m.setState(m.getNoCoinState());
    }

    public void crank() {
        System.out.println("Already cranked");
    }

    public void dispense() {
        System.out.println("We've a winner!");
        m.releaseBall();
        if (m.getGumballCount() > 0) {
            m.releaseBall();
            if (m.getGumballCount() > 0) {
                m.setState(m.getNoCoinState());
            } else {
                m.setState(m.getOutOfGumballState());
            }
        } else {
            m.setState(m.getOutOfGumballState());
        }
    }
}
