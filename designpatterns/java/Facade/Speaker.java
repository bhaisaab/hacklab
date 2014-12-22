public class Speaker {
    String name;
    public Speaker(String name) {
        this.name = name;
    }

    public void start() {
        System.out.println("Speaker " + name + " has started now now!");
    }

    public void stop() {
        System.out.println("Speaker " + name + " has ended now now!");
    }
}
