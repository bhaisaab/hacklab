public class SonyTV implements TV {

    public void on() {
        System.out.println("Sony TV ON!");
    }

    public void off() {
        System.out.println("Sony TV OFF!");
    }

    public void tuneChannel(int ch) {
        System.out.println("Sony TV channel:" + ch);
    }

}
