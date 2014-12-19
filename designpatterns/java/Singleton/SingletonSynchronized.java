public class SingletonSynchronized {
    private static SingletonSynchronized s_instance;

    private SingletonSynchronized() {
        System.out.println("Creating Singleton Class Object");
    }

    public static synchronized SingletonSynchronized getInstance() {
        if (s_instance == null) {
            s_instance = new SingletonSynchronized();
        }
        return s_instance;
    }

    public void output() {
        System.out.println("This is a single at your service!");
    }

}
