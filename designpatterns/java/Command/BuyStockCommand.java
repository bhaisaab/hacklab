public class BuyStockCommand implements Command {
    private Stock stock;

    public BuyStockCommand(Stock stock) {
        this.stock = stock;
    }

    public void execute() {
        this.stock.buy();
    }
}
