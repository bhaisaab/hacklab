public class Microphone {
    String type;
    public Microphone(String type) {
        this.type = type;
    }

    public void on() {
        System.out.println("Mic " + type + " is on now!");
    }

    public void off() {
        System.out.println("Mic " + type + " is off now!");
    }
}
