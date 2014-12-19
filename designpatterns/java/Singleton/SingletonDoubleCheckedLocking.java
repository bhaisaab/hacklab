// JVM 1.5+
public class SingletonDoubleCheckedLocking {
    private volatile static SingletonDoubleCheckedLocking s_instance;

    private SingletonDoubleCheckedLocking() {
        System.out.println("Creating Singleton Class Object");
    }

    public static SingletonDoubleCheckedLocking getInstance() {
        if (s_instance == null) {
            synchronized (SingletonDoubleCheckedLocking.class) {
                if (s_instance == null) {
                    s_instance = new SingletonDoubleCheckedLocking();
                }
            }
        }
        return s_instance;
    }

    public void output() {
        System.out.println("This is a single at your service!");
    }

}
