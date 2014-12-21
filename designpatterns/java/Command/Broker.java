import java.util.List;
import java.util.ArrayList;

public class Broker implements Runnable {
    private List<Command> stockQueue;

    public Broker() {
        stockQueue = new ArrayList<Command>();
    }

    public void order(Command newStockCommand) {
        stockQueue.add(newStockCommand);
    }

    public void run() {
        System.out.println("Running Broker Job queue");
        for (int i= 0; i < 10; i++) {
            if (stockQueue.size() > 0) {
                Command cmd = stockQueue.remove(0);
                cmd.execute();
            }
        }
    }
}
