
import java.util.Scanner;

public class SimpleCalculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean runCalc = true;
        while(runCalc) {
            System.out.println("Enter expression > "); 
            String input = scanner.nextLine();
            if (input.equalsIgnoreCase("done")) {
                runCalc = false;
                System.out.println("Exiting calculator. Goodbye!");
            } else {
                String[] parts = input.split(" ");
                if (parts.length != 3) {
                    System.out.println("Incorrect input.");
                    continue;
                }
                int num1 = Integer.parseInt(parts[0]);
                String operator = parts[1];
                int num2 = Integer.parseInt(parts[2]);
                int result = 0;
                switch (operator) {
                    case "+":
                        result = num1 + num2;
                        break;
                    case "-":
                        result = num1 - num2;
                        break;
                    case "*":
                        result = num1 * num2;
                        break;
                    case "/":
                        if (num2 == 0) {
                            System.out.println("Cannot divide by zero.");
                            continue; 
                        }
                        result = num1 / num2;
                        break;
                    default:
                        System.out.println("Incorrect input.");
                        break;
                }
                System.out.println("Result is " + result);
            }
        }
        scanner.close();
    }
}
