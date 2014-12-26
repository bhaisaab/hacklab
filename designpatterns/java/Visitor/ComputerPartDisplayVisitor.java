public class ComputerPartDisplayVisitor implements ComputerPartVisitor {

    int cost = 0;

    public ComputerPartDisplayVisitor() {
        cost = 0;
    }

    public int getTotalCost() {
        return cost;
    }

    @Override
    public void visit(Computer computer) {
      cost += 50;
      System.out.println("Displaying Computer.");
    }

    @Override
    public void visit(Mouse mouse) {
      cost += 5;
      System.out.println("Displaying Mouse.");
    }

    @Override
    public void visit(Keyboard keyboard) {
      cost += 10;
      System.out.println("Displaying Keyboard.");
    }

    @Override
    public void visit(Monitor monitor) {
      cost += 20;
      System.out.println("Displaying Monitor.");
    }
}
