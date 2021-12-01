public class Thread2 extends Thread {
    Shared mem;
    public Thread2(Shared mem) {
        super();
        this.mem = mem;
    }

    public void run() {
        int m;

        while (true) {
            try {
                Thread.sleep(300);
            } catch (InterruptedException e) {
                e.printStackTrace();
                break;
            }
            synchronized(mem) {
                if (mem.get() == -1) {
                    break;
                }

                System.out.println("\t\t\tThread 2, notify thread 1");
                mem.notify();
            }
        }
    }
}
