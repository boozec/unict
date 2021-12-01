public class MainThread {
    public static void main(String[] args) {
        Shared sh = new Shared();
        Thread1 t1 = new Thread1(sh);
        Thread2 t2 = new Thread2(sh);
        t1.start();
        t2.start();
    }
}
