public interface User {
    final static User NULL = new NullUser();
    String getName();
    boolean isRealUser();
    boolean isEnabled();
}
