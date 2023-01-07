public class Person {
    private String name;
    public void setName(String n) {
        this.name = n;
    }

    public void print() {
        System.out.println("Hello, "+ this.name);
    }
}
