public class Stock {
    private String name;

    public Stock(String name) {
        this.name = name;
    }

    public void buy() {
        System.out.println("Stock bought: " + name);
    }

    public void sell() {
        System.out.println("Stock sold: " + name);
    }
}
