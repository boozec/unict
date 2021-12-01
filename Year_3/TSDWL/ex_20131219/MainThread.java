public class MainThread {
    public static void main(String[] args) {
        Shared mem = new Shared();
        Thread1 t1 = new Thread1(mem);
        Thread2 t2 = new Thread2(mem);

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
