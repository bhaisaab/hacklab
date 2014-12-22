public class CoreOS implements LinuxHost {

    public void startVM(String name) {
        System.out.println("CoreOS does not support starting VM " + name);
    }

    public void stopVM(String name) {
        System.out.println("CoreOS does not support stopping VM " + name);
    }

    public void startDocker(String name) {
        System.out.println("Starting container " + name + " on Docker/CoreOS");
    }

    public void stopDocker(String name) {
        System.out.println("Stopping container " + name + " on Docker/CoreOS");
    }
}
