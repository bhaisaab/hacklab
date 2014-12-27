public class Sim {
    public static void main(String[] args) {
        Mediator m = new MediatorChatroom();

        Colleague r = new Colleague("Rob", m);
        Colleague b = new Colleague("Bob", m);
        Colleague c = new Colleague("Charlie", m);

        r.sendMessage("Hi it's Robbie");
        b.sendMessage("Hi it's Bobby");
        c.sendMessage("Hi it's Charlieee");

    }
}
