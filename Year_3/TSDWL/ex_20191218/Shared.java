public class Shared {
    private int x;

    public Shared() {
        x = (int) (Math.random() * (10-0+1)+0);
    }

    synchronized void set(int val) { x = val; }
    synchronized int get() { return x; }
}
