import java.io.*;
import java.net.*;

public class Client {

    public static void recv() throws IOException {
        Socket s = new Socket("localhost", 5000);
        InputStreamReader ir = new InputStreamReader(s.getInputStream());
        BufferedReader r = new BufferedReader(ir);

        System.out.println("Server says: " + r.readLine());
        r.close();
    }

    public static void main(String[] args) throws IOException {
        while (true)
        recv();
    }
}
