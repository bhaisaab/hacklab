public class Presentation {
    String name;
    public Presentation(String name) {
        this.name = name;
    }

    public void open() {
        System.out.println("Presentation is open = " + name);
    }

    public void close() {
        System.out.println("Presentation is closed = " + name);
    }
}
