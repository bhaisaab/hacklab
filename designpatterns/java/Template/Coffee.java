public class Coffee extends BeverageTemplate {

    void brew() {
        System.out.println("Filtering coffee");
    }

    void addCondiments() {
        System.out.println("Adding Cocoa powder");
    }

    boolean hookMilk() {
        return false;
    }

}
