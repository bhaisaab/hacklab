public interface LinuxHost {
    public void startVM(String vmName);
    public void stopVM(String vmName);
    public void startDocker(String cName);
    public void stopDocker(String cName);
}
