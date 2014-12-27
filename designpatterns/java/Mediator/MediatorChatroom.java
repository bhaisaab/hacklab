import java.util.Date;
import java.util.List;
import java.util.ArrayList;

public class MediatorChatroom implements Mediator {
    List<Colleague> colleagues = new ArrayList<Colleague>();

    public void registerColleague(Colleague user) {
        colleagues.add(user);
    }

    public void showMessage(Colleague user, String message) {
        String msg = new Date().toString() + "[" + user.getName() + "]: " + message;
        for (Colleague c: colleagues) {
            if (c.getName() != user.getName()) {
                c.printMessage(msg);
            }
        }
    }
}
