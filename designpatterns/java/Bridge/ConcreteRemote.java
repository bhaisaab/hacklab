public class ConcreteRemote extends RemoteControl {

    public ConcreteRemote(TV tv) {
        super(tv);
    }

    public void nextChannel() {
        setChannel(currentChannel+1);
    }
    public void prevChannel() {
        setChannel(currentChannel-1);
    }
}
