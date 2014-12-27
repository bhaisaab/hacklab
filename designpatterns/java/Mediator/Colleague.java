public class Colleague {
    String name;
    Mediator m;

    public Colleague(String name, Mediator m) {
        this.name = name;
        this.m = m;
        m.registerColleague(this);
    }

    public String getName() {
        return name;
    }

    public void printMessage(String msg) {
        System.out.println(name + " got: " + msg);
    }

    public void sendMessage(String message) {
        m.showMessage(this, message);
    }
}
