public abstract class RemoteControl {
    TV implementor;
    int currentChannel;
    public RemoteControl(TV tv) {
        this.implementor = tv;
    }

    public void on() {
        implementor.on();
    }
    public void off() {
        implementor.off();
    }
    public void setChannel(int ch) {
        currentChannel = ch;
        implementor.tuneChannel(ch);
    }

    public abstract void nextChannel();
    public abstract void prevChannel();
}
