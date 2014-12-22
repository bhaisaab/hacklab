public class FacadeSim {
    public static void main(String[] args) {

        ConferenceRoomFacade f = new ConferenceRoomFacade(new Microphone("Omni"), new Camera("Color"), new Presentation("Keynote"), new Speaker("John Doe"), new Audience(10));
        f.startTalk("Docker, Rocket, what's next");
        f.endTalk();
    }
}
