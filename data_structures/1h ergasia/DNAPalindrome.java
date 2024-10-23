import java.util.Scanner;


public class DNAPalindrome {
    

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter a DNA sequence: ");
        String dnaSequence = in.nextLine().trim();

        if (isValidDNASequence(dnaSequence)) {
            boolean isWatsonCrickPalindrome = isWatsonCrickComplementedPalindrome(dnaSequence);
            if (isWatsonCrickPalindrome) {
                System.out.println("The DNA sequence is a Watson-Crick complemented palindrome.");
            } else {
                System.out.println("The DNA sequence is NOT a Watson-Crick complemented palindrome.");
            }
        } else {
            System.out.println("Invalid DNA sequence.");
        }
    }

    private static boolean isValidDNASequence(String sequence) {
        // Έλεγχος για έγκυρη ακολουθία DNA
        return sequence.matches("[ATCG]+") && sequence.toUpperCase().equals(sequence);
    }

    private static boolean isWatsonCrickComplementedPalindrome(String sequence) {
        StringDoubleendedQueueImpl<Character> queue = new StringDoubleendedQueueImpl<>();

        for (char nucleotide : sequence.toCharArray()) {
            char complement = getComplement(nucleotide);
            queue.addFirst(complement);
        }

        for (char nucleotide : sequence.toCharArray()) {
            char complement = queue.removeFirst();
            if (nucleotide != complement) {
                return false;
            }
        }

        return true;
    }

    private static char getComplement(char nucleotide) {
        switch (nucleotide) {
            case 'A':
                return 'T';
            case 'T':
                return 'A';
            case 'C':
                return 'G';
            case 'G':
                return 'C';
            default:
                return ' '; 
        }
    }
}