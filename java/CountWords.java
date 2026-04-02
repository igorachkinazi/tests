public class CountWords {
    public static void main(String[] args) {
        String input = "This is a sample sentence with seven words.";
        System.out.println("Input: " + input);
        System.out.println("Word count: " + countWords(input));

        // Additional quick checks
        System.out.println("Empty count: " + countWords(""));
        System.out.println("Spaces only count: " + countWords("   \t\n  "));
        System.out.println("Multi-space count: " + countWords("one  two   three"));

        // reverse-words checks
        System.out.println("Reversed: '" + reverseWords(input) + "'");
        System.out.println("Reversed empty: '" + reverseWords("") + "'");
        System.out.println("Reversed spaced: '" + reverseWords("  hello   world  ") + "'");
    }

    public static String reverseWords(String text) {
        if (text == null || text.isBlank()) {
            return "";
        }

        String cleaned = text.replace(".", " ").trim();
        String[] words = cleaned.split("\\s+");
        StringBuilder sb = new StringBuilder();
        for (int i = words.length - 1; i >= 0; i--) {
            sb.append(words[i]);
            if (i > 0) {
                sb.append(" ");
            }
        }
        return sb.toString();
    }

    public static int countWords(String text) {
        if (text == null || text.isBlank()) {
            return 0;
        }
        // split on whitespace, trimming for safe count
        String[] words = text.trim().split("\\s+");
        return words.length;
    }
}
