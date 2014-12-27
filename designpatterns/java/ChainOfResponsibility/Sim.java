public class Sim {
    public static void main(String[] args) {
        ChainHandler spamh = new SpamHandler();
        ChainHandler fanh = new FanHandler();
        ChainHandler comh = new ComplaintHandler();
        ChainHandler pokemon = new CatchallHandler();

        spamh.setNextHandler(fanh);
        fanh.setNextHandler(comh);
        comh.setNextHandler(pokemon);

        spamh.handleRequest("this is a serious complaint");
        spamh.handleRequest("spam mail here bla bla");
        spamh.handleRequest("fan mail here bla bla");
        spamh.handleRequest("hello, random message here!");

    }
}
