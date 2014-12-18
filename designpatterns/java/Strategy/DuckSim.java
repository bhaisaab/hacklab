public class DuckSim {
    public static void main(String[] args) {
        Duck mallard = new MallardDuck();
        mallard.performQuack();
        mallard.performFly();
        mallard.display();

        Duck model = new ModelDuck();
        model.performQuack();
        model.setFlyBehaviour(new FlyWithJets());
        model.performFly();
        model.display();
    }
}
