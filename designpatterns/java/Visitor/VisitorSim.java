public class VisitorSim {
    public static void main(String[] args) {
        ComputerPart computer = new Computer();
        ComputerPartVisitor visitor = new ComputerPartDisplayVisitor();
        computer.accept(visitor);

        System.out.println("Total cost = " + visitor.getTotalCost());

    }
}
