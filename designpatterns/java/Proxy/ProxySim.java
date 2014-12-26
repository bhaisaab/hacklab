import java.lang.reflect.Proxy;

public class ProxySim {
    public static void main(String[] args) {
        Person ram = new PersonImpl();
        Person ownerProxy = getOwnerProxy(ram);
        Person nonOwnerProxy = getNonOwnerProxy(ram);

        ownerProxy.setName("Ram");
        System.out.println("Person name=" + ownerProxy.getName());
        System.out.println("Person rating=" + ownerProxy.getRating());
        try {
            ownerProxy.setRating(10);
        } catch (Exception e) {
            System.out.println("Owner proxy can't set it's own rating");
        }
        System.out.println("Person rating=" + ownerProxy.getRating());

        nonOwnerProxy.setName("Ram Bam Wham");
        System.out.println("Person name=" + nonOwnerProxy.getName());
        System.out.println("Person rating=" + nonOwnerProxy.getRating());
        try {
            nonOwnerProxy.setRating(4);
        } catch (Exception e) {
            System.out.println("nonOwner proxy can't set it's own rating");
        }
        System.out.println("Person rating=" + nonOwnerProxy.getRating());
    }

    // Dynamic Proxy generators:

    static Person getOwnerProxy(Person person) {
        return (Person) Proxy.newProxyInstance(person.getClass().getClassLoader(), person.getClass().getInterfaces(), new OwnerInvocationHandler(person));
    }

    static Person getNonOwnerProxy(Person person) {
        return (Person) Proxy.newProxyInstance(person.getClass().getClassLoader(), person.getClass().getInterfaces(), new NonOwnerInvocationHandler(person));
    }

}
