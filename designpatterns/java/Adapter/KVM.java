public class KVM implements Hypervisor {
    public KVM() {
    }

    public void startVM(String name) {
        System.out.println("KVM starting VM " + name);
    }

    public void stopVM(String name) {
        System.out.println("KVM stopping VM " + name);
    }
}
