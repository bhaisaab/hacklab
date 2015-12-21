public class NullUser implements User {

    public String getName() {
        return "NullUser";
    }

    public boolean isRealUser() {
        return false;
    }

    public boolean isEnabled() {
        return false;
    }
}
