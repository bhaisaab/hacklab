import java.rmi.*;
import java.rmi.server.*;

public class MyRemoteImpl extends UnicastRemoteObject implements MyRemote {

    public MyRemoteImpl() throws RemoteException {}

    public String sayHello() throws RemoteException {
        System.out.println("RMI running sayHello()");
        return "Server says HI";
    }

    public static void main(String[] args) {
        try {
            MyRemote service = new MyRemoteImpl();
            Naming.rebind("RemoteHello", service);
        } catch (Exception pokemon) {
            pokemon.printStackTrace();
        }
    }

}
