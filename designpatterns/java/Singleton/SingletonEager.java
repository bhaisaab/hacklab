public class SingletonEager {
    private static SingletonEager s_instance = new SingletonEager();

    private SingletonEager() {
        System.out.println("Creating Singleton Class Object");
    }

    public static SingletonEager getInstance() {
        return s_instance;
    }

    public void output() {
        System.out.println("This is a single at your service!");
    }

}
