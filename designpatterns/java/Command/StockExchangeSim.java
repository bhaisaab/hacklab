public class StockExchangeSim {
    public static void main(String[] args) {
        Broker b = new Broker();
        Thread exchange = new Thread(b, "Broker Exchange Thread");
        exchange.start();

        Stock google = new Stock("Google");
        Stock apple = new Stock("Apple");
        Stock microsoft = new Stock("Microsoft");
        Stock facebook = new Stock("Facebook");

        b.order(new BuyStockCommand(google));
        b.order(new BuyStockCommand(apple));
        b.order(new SellStockCommand(facebook));
        b.order(new BuyStockCommand(microsoft));
        b.order(new SellStockCommand(apple));
        b.order(new SellStockCommand(microsoft));
        b.order(new BuyStockCommand(facebook));
        b.order(new SellStockCommand(google));


    }
}
