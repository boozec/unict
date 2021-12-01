public class Thread1 extends Thread {
    private Shared mem;

    public Thread1(Shared mem) {
        super();
        this.mem = mem;
    }

    public void run() {
        int xrand;
        int m;
        while (true) {
            synchronized(mem) {
                m = mem.get();
                if (m >= 1 && m <= 5) {
                    xrand = (int) (Math.random() * (10-1+1)+1);
                    System.out.printf("Thread 1: (%d, %d)\n", m, xrand);
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
