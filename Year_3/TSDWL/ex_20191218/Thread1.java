public class Thread1 extends Thread {
    Shared mem;
    public Thread1(Shared mem) {
        super();
        this.mem = mem;
    }

    public void run() {
        int m;

        while (true) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
                break;
            }
            m = (int) (Math.random() * (10-0+1)+0);

            synchronized(mem) {
                System.out.printf("Thread 1, x = %d, m = %d\n", mem.get(), m);
                if (mem.get() == -1) {
                    break;
                } else if(mem.get() == m) {
                    System.out.println("RISPOSTA CORRETTA");
                    mem.set(-1);
                } else if(Math.abs(m-mem.get()) > 5) {
                    try {
                        System.out.println("risposta MOLTO sbagliata");
                        System.out.println("Thread 1 going to sleep");
                        mem.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                        break;
                    }
                } else {
                    System.out.println("risposta sbagliata");
                }
            }
        }
    }
}
