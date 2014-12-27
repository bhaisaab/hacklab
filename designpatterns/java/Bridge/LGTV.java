public class LGTV implements TV {

    public void on() {
        System.out.println("LG TV ON!");
    }

    public void off() {
        System.out.println("LG TV OFF!");
    }

    public void tuneChannel(int ch) {
        System.out.println("LG TV channel:" + ch);
    }

}
