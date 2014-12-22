public class Audience {
    int count = 0;
    public Audience(int count) {
        this.count = count;
    }

    public void enter() {
        System.out.println(count + " no. of people entered talk");
    }

    public void exit() {
        System.out.println(count + " no. of people exited talk");
    }

}
