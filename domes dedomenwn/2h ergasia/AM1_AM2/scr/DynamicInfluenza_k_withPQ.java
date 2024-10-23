import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DynamicInfluenza_k_withPQ {
    public static void main(String[] args) {

        if (args.length != 2) {
            System.out.println("error");
            System.exit(1);
        }

        String inputFile = args[1];
        int k = Integer.parseInt(args[0]);

        if (k <= 0) {
            System.out.println("Invalid value of k. Please enter a positive integer.");
            System.exit(1);
        }
		try {
            PQ priorityQueue = new PQ();

            Scanner fileScanner = new Scanner(new File(inputFile));

            int lineCount = 0;
            while (fileScanner.hasNextLine()) {
                lineCount++;
                String data = fileScanner.nextLine().trim();
                String[] info = data.split(" ");
                int id = Integer.parseInt(info[0]);
                String name = info[1];
                int population = Integer.parseInt(info[2]);
                int cases = Integer.parseInt(info[3]);

                City city = new City(id, name, population, cases);
                priorityQueue.insert(city);

                if (lineCount % 5 == 0) {
                    printTopCities(priorityQueue, k);
                }
            }

            fileScanner.close();

        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + e.getMessage());
        }
    }

    private static void printTopCities(PQ priorityQueue, int k) {
        PQ tempQueue = new PQ();
        System.out.println("\nTop " + k + " cities with lowest influenza density:");
        for (int i = 0; i < k; i++) {
            if (priorityQueue.isEmpty()) {
                break;
            }
            City city = priorityQueue.getMin();
            tempQueue.insert(city);
            System.out.println(city.getName());
        }
        while (!tempQueue.isEmpty()) {
            priorityQueue.insert(tempQueue.getMin());
        }
    }
}