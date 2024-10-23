import java.io.File;
import java.io.FileNotFoundException;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Scanner;

public class Dynamic_Median {
    public static void main(String[] args) {
		
		if (args.length != 1 ) {
            System.out.println("error");
            System.exit(1);
        }

        String inputFile = args[0];
		
		try {
            PriorityQueue<Double> maxHeap = new PriorityQueue<>(Comparator.reverseOrder());
            PriorityQueue<Double> minHeap = new PriorityQueue<>();
            int count = 0;

            Scanner fileScanner = new Scanner(new File(inputFile));

            while (fileScanner.hasNextLine()) {
                String data = fileScanner.nextLine().trim();
                String[] info = data.split(" ");
                int cases = Integer.parseInt(info[3]);
                int population = Integer.parseInt(info[2]);

                double density = calculateDensity(cases, population);

                if (maxHeap.isEmpty() || density <= maxHeap.peek()) {
                    maxHeap.offer(density);
                } else {
                    minHeap.offer(density);
                }

                balanceHeaps(maxHeap, minHeap);

                count++;

                if (count % 5 == 0) {
                    double median = calculateMedian(maxHeap, minHeap);
					median = Math.round(median * 10.0) / 10.0;
                    System.out.println("Median: " + median);
                }
            }

            fileScanner.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + e.getMessage());
        }
    }

    private static double calculateDensity(int cases, int population) {
        return ((double) cases / population) * 50000;
    }

    private static void balanceHeaps(PriorityQueue<Double> maxHeap, PriorityQueue<Double> minHeap) {
        PriorityQueue<Double> smallerHeap = maxHeap.size() > minHeap.size() ? minHeap : maxHeap;
        PriorityQueue<Double> largerHeap = maxHeap.size() > minHeap.size() ? maxHeap : minHeap;

        if (largerHeap.size() - smallerHeap.size() >= 2) {
            smallerHeap.offer(largerHeap.poll());
        }
    }

    private static double calculateMedian(PriorityQueue<Double> maxHeap, PriorityQueue<Double> minHeap) {
        PriorityQueue<Double> smallerHeap = maxHeap.size() > minHeap.size() ? minHeap : maxHeap;
        PriorityQueue<Double> largerHeap = maxHeap.size() > minHeap.size() ? maxHeap : minHeap;

        if (smallerHeap.size() == largerHeap.size()) {
            return (double) (smallerHeap.peek() + largerHeap.peek()) / 2;
        } else {
            return largerHeap.peek();
        }
    }
}
