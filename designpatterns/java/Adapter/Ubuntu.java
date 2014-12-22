public class Ubuntu implements LinuxHost {

    public void startVM(String name) {
        System.out.println("Starting VM " + name + " on KVM/Ubuntu");
    }

    public void stopVM(String name) {
        System.out.println("Stopping VM " + name + " on KVM/Ubuntu");
    }

    public void startDocker(String name) {
        System.out.println("Starting container " + name + " on Docker/Ubuntu not supported");
    }

    public void stopDocker(String name) {
        System.out.println("Stopping container " + name + " on Docker/Ubuntu not supported");
    }
}
