public class GoaVacationBuilder extends AbstractBuilder {

    public void buildDay() {
        this.addHotel("Taj", "One");
        this.addTicket("Bungee", "One");
        this.addSpecialEvent("Beach beers", "One");

        this.addHotel("BlueSpas", "Two");
        this.addTicket("Paragliding", "Two");
        this.addSpecialEvent("Casino", "Two");
    }
}
