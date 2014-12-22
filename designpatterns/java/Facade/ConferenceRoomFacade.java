public class ConferenceRoomFacade {
    Microphone mic;
    Camera cam;
    Presentation ppt;
    Speaker speaker;
    Audience audi;

    public ConferenceRoomFacade(Microphone mic, Camera cam, Presentation ppt, Speaker speaker, Audience audi) {
        this.mic = mic;
        this.cam = cam;
        this.ppt = ppt;
        this.speaker = speaker;
        this.audi = audi;
    }

    public void startTalk(String talk) {
        System.out.println("Our next speaker is going to talk about - " + talk);
        audi.enter();
        mic.on();
        cam.on();
        ppt.open();
        speaker.start();
    }

    public void endTalk() {
        System.out.println("Thanks for coming to the talk! See you in next conference");
        speaker.stop();
        ppt.close();
        cam.off();
        mic.off();
        audi.exit();
    }

}
