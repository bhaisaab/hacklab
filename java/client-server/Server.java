import java.io.*;
import java.net.*;
import java.lang.*;

public class Server {
    static ServerSocket serverSock;
    static long counter = 0;

    public static void serve(Socket s) throws IOException {
        PrintWriter w = new PrintWriter(s.getOutputStream());
        w.println("hello! you're visitor: " + counter);
        w.close();
        counter++;
        System.out.println("served: " + counter);
    }

    public static Socket accept() throws IOException {
        return serverSock.accept();
    }

    public static ServerSocket init() throws IOException {
        if (serverSock == null)
            serverSock = new ServerSocket(5000);
        return serverSock;
    }

    public static void main(String[] args) throws IOException {
        init();
        while(true) {
            Socket s = serverSock.accept();
            serve(s);
        }
    }
}
