public class Cloud implements Hypervisor {

    public void start(String hypervisor, String name) {
        if (hypervisor.equals("Rocket")) {
            System.out.println("Rocket launched: " + name);
        } else {
            Hypervisor adapter = new HypervisorAdapter(hypervisor);
            adapter.start(hypervisor, name);
        }
    }

    public void stop(String hypervisor, String name) {
        if (hypervisor.equals("Rocket")) {
            System.out.println("Rocket called back: " + name);
        } else {
            Hypervisor adapter = new HypervisorAdapter(hypervisor);
            adapter.stop(hypervisor, name);
        }
    }
}
