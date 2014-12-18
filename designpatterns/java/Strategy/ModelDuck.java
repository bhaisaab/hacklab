public class ModelDuck extends Duck {
    public ModelDuck() {
        quackBehaviour = new Squeak();
        flyBehaviour = new FlyNoWay();
    }

    public void display() {
        System.out.println("I'm a model Duck!");
    }
}
