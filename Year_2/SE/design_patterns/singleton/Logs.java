public class Logs {
    private static Logs log;

    private Logs(){}

    public static Logs getInstanceLogs() {
        if(log == null) log = new Logs();
        return log;
    }
}
