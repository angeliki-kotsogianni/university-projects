import java.util.Scanner; 
public class PrefixToInfix {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter prefix expression: ");
        String prefix = in.nextLine().trim();


        try {
			String infixExpression = Converter.convertToInfix(prefix);
            System.out.println("Infix expression: " + infixExpression);
        } catch (IllegalArgumentException e) {
            System.out.println("Invalid prefix expression: " + e.getMessage());
        }
    }
}