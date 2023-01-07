import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<String> l = List.of("to", "speak", "the", "truth", "and", "pay", "your", "debts");
        l.stream()
            .map(x -> x.charAt(0))
            .forEach(c -> System.out.print(c));
    }
}

