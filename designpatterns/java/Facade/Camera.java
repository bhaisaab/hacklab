public class Camera {
    String type;
    public Camera(String type) {
        this.type = type;
    }

    public void on() {
        System.out.println("Camera " + type + " is on now!");
    }

    public void off() {
        System.out.println("Camera " + type + " is off now!");
    }
}
