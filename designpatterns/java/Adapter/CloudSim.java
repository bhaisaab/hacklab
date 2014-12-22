public class CloudSim {
    public static void main(String[] args) {
        Hypervisor h = new KVM();
        h.startVM("vm1");
        h.stopVM("vm1");

        Container docker = new Docker();
        Hypervisor hh = new HypervisorAdapter(docker);
        hh.startVM("k2");
        hh.stopVM("k2");
    }
}
