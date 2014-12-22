public class Docker implements Container {

    public void startContainer(String name) {
        System.out.println("Docker starting  " + name);
    }

    public void stopContainer(String name) {
        System.out.println("Docker stopping  " + name);
    }
}
