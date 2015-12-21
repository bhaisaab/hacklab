public class RealUser implements User {

    private String name;

    public RealUser() {
        this.name = "Real User";
    }

    public RealUser(final String name) {
        this.name = name;
    }

    public String getName() {
        return "Real User";
    }

    public boolean isRealUser() {
        return true;
    }

    public boolean isEnabled() {
        return true;
    }
}
