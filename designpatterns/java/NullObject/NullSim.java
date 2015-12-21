public class NullSim {
    public static void main(String[] args) {
        User a = new RealUser();
        User b = new NullUser();
        User c = User.NULL;

        System.out.println("User A (real): " + a.getName() + ", is real = " + a.isRealUser() + ", is enabled = " + a.isEnabled());
        System.out.println("User B (null): " + b.getName() + ", is real = " + b.isRealUser() + ", is enabled = " + b.isEnabled());
        System.out.println("User C (User.NULL): " + c.getName() + ", is real = " + c.isRealUser() + ", is enabled = " + c.isEnabled());

        System.out.println("Compare A&B: " + a.equals(b));
        System.out.println("Compare B&C: " + b.equals(c));
    }
}
