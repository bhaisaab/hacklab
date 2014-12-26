import java.util.Random;

public class HasCoinState implements State {
    GumballMachine m;
    Random randomWinner = new Random(System.currentTimeMillis());

    public HasCoinState(GumballMachine m) {
        this.m = m;
    }

    public void insertCoin() {
        System.out.println("Already have a coin");
    }

    public void ejectCoin() {
        System.out.println("Take you money!");
        m.setState(m.getNoCoinState());
    }

    public void crank() {
        System.out.println("Cranking!");
        int winner = randomWinner.nextInt(10);
        if (winner == 0 && m.getGumballCount() > 1) {
            m.setState(m.getWinnerState());
        } else {
            m.setState(m.getGumballSoldState());
        }
    }

    public void dispense() {
        System.out.println("You need to crank first!");
    }
}
