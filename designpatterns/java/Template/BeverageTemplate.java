public abstract class BeverageTemplate {
    public final void make() {
        boilWater();
        brew();
        if (hookMilk()) {
            addMilk();
        }
        pourInCup();
        addCondiments();
    }

    abstract void brew();
    abstract void addCondiments();

    boolean hookMilk() {
        return false;
    }

    private final void boilWater() {
        System.out.println("Boiling water");
    }

    private final void addMilk() {
        System.out.println("Adding Milk");
    }

    private final void pourInCup() {
        System.out.println("Pouring into cup");
    }
}
