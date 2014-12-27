public abstract class AbstractBuilder {

    Vacation vacation = new Vacation();

    public abstract void buildDay();

    public void addHotel(String name, String day) {
        vacation.add(new Event("Hotel: "+name, day));
    }

    public void addTicket(String name, String day) {
        vacation.add(new Event("Ticket: " + name, day));
    }

    public void addSpecialEvent(String name, String day) {
        vacation.add(new Event("Special: " + name, day));
    }

    public Vacation getVacationPlanner() {
        return vacation;
    }
}
