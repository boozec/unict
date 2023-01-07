public class Main {
    public static void main(String[] args) {
        Student s = new Student();
        s.setName("Santo");
        s.setMatr("1948");

        s.print();

        Person p = s;
        // That's not compile
        // p.setMatr("1949");
        p.setName("John");
        p.print();

        // s.name is equals to p.name, so the code below print
        // Hello, John[...]
        s.print();
    }
}
