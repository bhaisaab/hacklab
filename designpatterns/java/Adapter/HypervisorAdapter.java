public class HypervisorAdapter implements Hypervisor {
    LinuxHost host;

    public HypervisorAdapter(String name) {
        if (name.equals("Docker")) {
            this.host = new CoreOS();
        } else {
            this.host = new Ubuntu();
        }
    }

    public void start(String hypervisor, String name) {
        if (hypervisor.equals("Docker")) {
            host.startDocker(name);
        } else {
            host.startVM(name);
        }
    }

    public void stop(String hypervisor, String name) {
        if (hypervisor.equals("Docker")) {
            host.stopDocker(name);
        } else {
            host.stopVM(name);
        }
    }
}
