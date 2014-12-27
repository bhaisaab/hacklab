public class Sim {
    public static void main(String[] args) {
        AbstractBuilder goa = new GoaVacationBuilder();
        AbstractBuilder ams = new AmsterdamVacationBuilder();

        goa.buildDay();
        ams.buildDay();

        Vacation goaVacationPlan = goa.getVacationPlanner();
        Vacation amsVacationPlan = ams.getVacationPlanner();

        System.out.println(goaVacationPlan);
        System.out.println(amsVacationPlan);

    }
}
