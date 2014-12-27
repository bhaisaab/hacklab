public class Sim {
    public static void main(String[] args) {

        TV sony = new SonyTV();
        TV lg = new LGTV();

        RemoteControl sr = new ConcreteRemote(sony);
        RemoteControl lr = new ConcreteRemote(lg);

        sr.on();
        sr.setChannel(10);
        sr.nextChannel();
        sr.nextChannel();
        sr.prevChannel();
        sr.off();

        lr.on();
        lr.setChannel(10);
        lr.nextChannel();
        lr.nextChannel();
        lr.prevChannel();
        lr.off();

    }
}
