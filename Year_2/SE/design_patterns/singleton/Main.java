public class Main {
    public static void main(String[] args) {
        Logs l = Logs.getInstanceLogs();
        Logs l2 = Logs.getInstanceLogs();

        // Prints "true"
        System.out.println(l == l2);

        // Error, because the constructor is private
        // Logs l3 = new Logs();
    }
}
