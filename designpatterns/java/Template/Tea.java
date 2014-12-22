public class Tea extends BeverageTemplate {

    void brew() {
        System.out.println("Dipping tea bags");
    }

    void addCondiments() {
        System.out.println("Adding caramel");
    }

    @Override
    boolean hookMilk() {
        return true;
    }

}
