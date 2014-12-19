public class Singleton {
    private static Singleton s_instance;

    private Singleton() {
        System.out.println("Creating Singleton Class Object");
    }

    public static Singleton getInstance() {
        if (s_instance == null) {
            s_instance = new Singleton();
        }
        return s_instance;
    }

    public void output() {
        System.out.println("This is a single at your service!");
    }
}
