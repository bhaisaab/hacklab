public class PrototypeSim {
    public static void main(String[] args) {
        CloneFactory fac = new CloneFactory();
        Sheep sally = new Sheep();

        Sheep clonedSheep = (Sheep) fac.getClone(sally);

        System.out.println(sally);
        System.out.println(clonedSheep);

        System.out.println("Sally hashcode: " + System.identityHashCode(sally));
        System.out.println("Clone sheep hashcode: " + System.identityHashCode(clonedSheep));
    }
}
