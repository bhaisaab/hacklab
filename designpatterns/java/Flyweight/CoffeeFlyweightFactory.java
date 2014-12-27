import java.util.Map;
import java.util.HashMap;

public class CoffeeFlyweightFactory {
    private Map<String, CoffeeFlyweight> flavours = new HashMap<String, CoffeeFlyweight>();

    public CoffeeFlyweight getFlyweight(String key) {
        if (!flavours.containsKey(key)) {
            flavours.put(key, new CoffeeFlyweight(key));
        }
        return flavours.get(key);
    }
}
