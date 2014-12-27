public class CoffeeFlyweight {
    private final String name;

    public CoffeeFlyweight(String name) {
        this.name = name;
    }
    public String toString() {
        return name + " h#:" + System.identityHashCode(this);
    }
}
