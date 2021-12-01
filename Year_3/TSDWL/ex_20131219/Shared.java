public class Shared {
    private int m;

    public Shared() {
        m = (int) (Math.random() * (11-1+1)+1);
    }

    synchronized public void set(int val) { m = val; }
    synchronized public int get() { return m; }
}
