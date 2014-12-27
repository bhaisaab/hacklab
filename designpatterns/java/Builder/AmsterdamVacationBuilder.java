public class AmsterdamVacationBuilder extends AbstractBuilder {

    public void buildDay() {
        this.addHotel("Regient", "One");
        this.addTicket("Henekin bar", "One");
        this.addSpecialEvent("Beer biking", "One");

        this.addHotel("Regient", "Two");
        this.addTicket("City Tour", "Two");
        this.addSpecialEvent("Tulip farming", "Two");
    }
}
