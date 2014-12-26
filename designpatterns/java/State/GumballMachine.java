public class GumballMachine {
    State noCoinState;
    State hasCoinState;
    State gumballSoldState;
    State outOfGumballState;
    State winnerState;

    State currentState;
    private int count = 0;

    public GumballMachine(int n) {
        this.count = n;

        noCoinState = new NoCoinState(this);
        hasCoinState = new HasCoinState(this);
        gumballSoldState = new GumballSoldState(this);
        outOfGumballState = new OutOfGumballState(this);
        winnerState = new WinnerState(this);

        if (count > 0) {
            currentState = noCoinState;
        } else {
            currentState = outOfGumballState;
        }
    }

    public void insertCoin() {
        currentState.insertCoin();
    }

    public void ejectCoin() {
        this.currentState.ejectCoin();
    }

    public void crank() {
        this.currentState.crank();
        this.currentState.dispense();
    }

    public void setState(State s) {
        this.currentState = s;
    }

    public State getNoCoinState() {
        return noCoinState;
    }

    public State getHasCoinState() {
        return hasCoinState;
    }

    public State getGumballSoldState() {
        return gumballSoldState;
    }

    public State getOutOfGumballState() {
        return outOfGumballState;
    }

    public State getWinnerState() {
        return winnerState;
    }

    public int getGumballCount() {
        return count;
    }

    public void releaseBall() {
        if (count > 0) {
            count--;
            System.out.println("Releasing Gumball!");
        }
    }

    public void refill(int i) {
        if (i > 0) {
            count += i;
            System.out.println("Gumball machine refilled with gumballs: " + count);
            setState(getNoCoinState());
        }
    }

    public String toString() {
        return "Gumball pro has " + count + "  gumballs!\n";
    }
}
