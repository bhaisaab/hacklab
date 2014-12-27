public abstract class ChainHandler {

    protected String blacklist;
    protected ChainHandler nextHandler;

    public void setNextHandler(ChainHandler nL) {
        nextHandler = nL;
    }

    public void handleRequest(String msg) {
        if (!msg.contains(blacklist)) {
            nextHandler.handleRequest(msg);
        } else {
            System.out.println("Handler::" + blacklist + " " + msg);
        }
    }
}
