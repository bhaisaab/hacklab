public class AdapterSim {
    public static void main(String[] args) {
        Hypervisor h = new Cloud();

        h.start("KVM", "vm-1");
        h.start("Docker", "container-1");
        h.start("Rocket", "container-x");

        h.stop("KVM", "vm-2");
        h.stop("Docker", "container-9");
        h.stop("Rocket", "container-y");
   }
}
