public class Student extends Person {
    private String matr;

    public void setMatr(String m) {
        this.matr = m;
    }

    @Override
    public void print() {
        super.print();
        System.out.println("I'm "+ this.matr);
    }
}
