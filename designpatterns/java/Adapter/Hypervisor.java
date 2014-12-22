public interface Hypervisor {
    public void start(String hypervisor, String vmName);
    public void stop(String hypervisor, String vmName);
}
