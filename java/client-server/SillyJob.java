import java.lang.*;
import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;

public class SillyJob {

    public static class TServerHandler implements Runnable {
        Socket s;
        long counter;
        public TServerHandler(Socket s, long counter) {
            this.s = s;
            this.counter = counter;
        }

        @Override
        public void run() {
            try {
                PrintWriter w = new PrintWriter(s.getOutputStream());
                w.println("hello! you're visitor: " + counter);
                w.close();
                System.out.println("served: " + counter);
            } catch (IOException e) {
            }
        }
    }

    public static class TServer implements Runnable {
        long counter = 0;
        ServerSocket ss;
        public TServer() throws IOException {
            ss = new ServerSocket(5000);
            System.out.println("Starting a server");
        }

        @Override
        public void run() {
            final ExecutorService pool = Executors.newFixedThreadPool(10);
            try {
                while (true) {
                    Socket s = ss.accept();
                    counter++;
                    pool.submit(new TServerHandler(s, counter));
                }
            } catch (IOException e) {}
        }
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Running silly threaded server/clients");
        Thread serverT = new Thread(new TServer());
        serverT.start();
        System.out.println("Back to main...");
    }
}
