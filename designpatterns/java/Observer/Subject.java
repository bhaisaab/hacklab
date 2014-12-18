public interface Subject {
    public void registerObserver(Observer o);
    public void deregisterObserver(Observer o);
    public void notifyObservers();
}
