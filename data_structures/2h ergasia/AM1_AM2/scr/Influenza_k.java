import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Influenza_k {
	
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
			City[] cities = readFile(inputFile);

			quicksort(cities, 0, cities.length - 1);
			
			if (k >= cities.length) {
				System.out.println("Invalid value of k. Please enter a value smaller than the total number of cities.");
				System.exit(1);
			}

			System.out.println("The top k cities are:");
			for (int i = 0; i < k; i++) {
				System.out.println(cities[i].getName());
			}
		} catch (FileNotFoundException e) {
			System.out.println("File not found: " + e.getMessage());
		}
    }

    private static City[] readFile(String fileName) throws FileNotFoundException {
        File file = new File(fileName);
		Scanner myReader = new Scanner(file);
		int i =0;
		while (myReader.hasNextLine()) {
			i++;
			myReader.nextLine();
		}
		myReader.close();
        City[] cities = new City[i];
		Scanner myReader2 = new Scanner(file);

        for (int k = 0; k < i; k++) {
			String data = myReader2.nextLine().trim();
			String[] info = data.split(" ");
            int id = Integer.parseInt(info[0]);
            String name = info[1];
            int population = Integer.parseInt(info[2]);
            int cases = Integer.parseInt(info[3]);
            cities[k] = new City(id, name, population, cases);
        }
		
		myReader2.close();

        return cities;
    }

    private static void quicksort(City[] cities, int l, int r) {
        if (r <= l) return;
        int i = partition(cities, l, r);
        quicksort(cities, l, i - 1);
        quicksort(cities, i + 1, r);
    }

    static int partition(City[] cities, int l, int r){
		int i = l-1, j = r;  City v = cities[r];
		for (;;){ 
			while (less(cities[++i], v)) ;
			while (less(v, cities[--j]))
				if (j == l) break;
			if (i >= j) break;
			exch(cities, i, j);
		}
		exch(cities, i, r);
		return i; 
	}

    private static void exch(City[] cities, int i, int j) {
        City temp = cities[i];
        cities[i] = cities[j];
        cities[j] = temp;
    }
	
	private static boolean less(City city1, City city2) {
        return city1.compareTo(city2) < 0;
    }

}
