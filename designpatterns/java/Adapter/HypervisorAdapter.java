public class HypervisorAdapter implements Hypervisor {
    private Container container;
    public HypervisorAdapter(Container container) {
        this.container = container;
    }

    public void startVM(String name) {
        container.startContainer(name);
    }

    public void stopVM(String name) {
        container.stopContainer(name);
    }

}
