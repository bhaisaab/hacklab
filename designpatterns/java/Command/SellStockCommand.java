public class SellStockCommand implements Command {
    private Stock stock;

    public SellStockCommand(Stock stock) {
        this.stock = stock;
    }

    public void execute() {
        this.stock.sell();
    }
}
