public class WeatherStationSim {
    public static void main(String[] args) {
        WeatherData wd = new WeatherData();

        StandardDisplay sd = new StandardDisplay(wd);
        MobileDisplay md = new MobileDisplay(wd);

        wd.setMeasurements(80, 65, 30.4f);
        wd.setMeasurements(75, 45, 50.1f);
        wd.setMeasurements(50, 95, 10.2f);
    }
}
