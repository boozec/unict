public class Thread2 extends Thread {
    private Shared mem;

    public Thread2(Shared mem) {
        super();
        this.mem = mem;
    }

    public void run() {
        int xrand;
        int m;
        while (true) {
            synchronized(mem) {
                m = mem.get();
                if (m >= 6 && m <= 10) {
                    xrand = (int) (Math.random() * (10-1+1)+1);
                    System.out.printf("\t\t\tThread 2: (%d, %d)\n", m, xrand);
                    mem.set(xrand);
                    mem.notifyAll();
                } else {
                    try {
                        mem.wait();
                    } catch(InterruptedException e) {
                        e.printStackTrace();
                        break;
                    }
                }
            }
        }
    }
}
