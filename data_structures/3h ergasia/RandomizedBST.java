import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class RandomizedBST implements TaxEvasionInterface {

    private class TreeNode {
        LargeDepositor item;
        TreeNode left;
        TreeNode right;
        int N;

        TreeNode(LargeDepositor item) {
            this.item = item;
            this.N = 1;
        }
    }

    private TreeNode root;

  
    private TreeNode rotateRight(TreeNode h) {
        TreeNode x = h.left;
        h.left = x.right;
        x.right = h;
        x.N = h.N;
        h.N = 1 + size(h.left) + size(h.right);
        return x;
    }

    
    private TreeNode rotateLeft(TreeNode h) {
        TreeNode x = h.right;
        h.right = x.left;
        x.left = h;
        x.N = h.N;
        h.N = 1 + size(h.left) + size(h.right);
        return x;
    }

    
    private int size(TreeNode x) {
        return (x == null) ? 0 : x.N;
    }

  
    @Override
    public void insert(LargeDepositor item) {
        root = insertR(root, item);
    }

    private TreeNode insertR(TreeNode h, LargeDepositor x) { //αν υπαρχει το αφμ εμφανιζει καταλληλο μηνυμα
        if (h == null)
            return new TreeNode(x);

        if (containsAFM(h, x.key())) {
            System.out.println("Error: LargeDepositor with AFM " + x.key() + " already exists.");
            System.exit(1);
        }

        if (Math.random() * (h.N + 1) < 1.0) {
            return insertAsRoot(x, h);
        }

        if (x.key() < h.item.key())
            h.left = insertR(h.left, x);
        else
            h.right = insertR(h.right, x);

        h.N++;
        return h;
    }

    private boolean containsAFM(TreeNode h, int afm) { //ελεγχει αν υπαρχει το δοσμενο αφμ
        if (h == null)
            return false;

        if (afm == h.item.key())
            return true;
        else if (afm < h.item.key())
            return containsAFM(h.left, afm);
        else
            return containsAFM(h.right, afm);
    }

    private TreeNode insertAsRoot(LargeDepositor item, TreeNode h) { //η βοηθητικη μεθοδος που κανει εισαγωγη στη ριζα του item στο υποδεντρο που ξεκινα απο τον h
        if (h == null)
            return new TreeNode(item);

        if (item.key() < h.item.key()) {
            h.left = insertAsRoot(item, h.left);
            h = rotateRight(h);
        } else {
            h.right = insertAsRoot(item, h.right);
            h = rotateLeft(h);
        }

        h.N = 1 + size(h.left) + size(h.right);
        return h;
    }

   
    @Override
    public void load(String filename) throws FileNotFoundException {
        File file = new File(filename);
		Scanner myReader = new Scanner(file);
		int i =0;
		while (myReader.hasNextLine()) {
			i++;
			myReader.nextLine();
		}
		myReader.close();
    }

 
    @Override
    public void updateSavings(int AFM, double savings) {
        root = updateSavingsHelper(root, AFM, savings);
    }


    private TreeNode updateSavingsHelper(TreeNode h, int AFM, double savings) { //βπηθητικη μεθοδος για την updateSavings
        if (h == null) {
            System.out.println("LargeDepositor with AFM " + AFM + " not found.");
            return null;
        }

        if (AFM == h.item.key()) {
            h.item.setSavings(savings);
            return h;
        } else if (AFM < h.item.key()) {
            h.left = updateSavingsHelper(h.left, AFM, savings);
        } else {
            h.right = updateSavingsHelper(h.right, AFM, savings);
        }

        h.N = 1 + size(h.left) + size(h.right);
        return h;
    }

    @Override
    public LargeDepositor searchByAFM(int AFM) {
        TreeNode result = searchByAFMHelper(root, AFM);
		if (result!=null){
			System.out.println(result.item);
			return result.item;
        }else{
			System.out.println("The given information does not exist");
			return null;
		}
    }


    private TreeNode searchByAFMHelper(TreeNode h, int AFM) {//βοηθητικη μεθοδος για την searchByAFM
        if (h == null)
            return null;

        if (AFM == h.item.key())
            return h;
        else if (AFM < h.item.key())
            return searchByAFMHelper(h.left, AFM);
        else
            return searchByAFMHelper(h.right, AFM);
    }

   
    @Override
    public List<LargeDepositor> searchByLastName(String last_name) {
        List<LargeDepositor> result = new List<>();
        searchByLastNameHelper(root, last_name, result);
        return result;
    }

   
    private void searchByLastNameHelper(TreeNode h, String last_name, List<LargeDepositor> result) {//βοηθητικη μεθοδος για την searchByLastName
        if (h == null)
            return;

        searchByLastNameHelper(h.left, last_name, result);

        if (h.item.getLastName().equals(last_name)) {
            result.insertAtFront(h.item);
            if (result.getSize() >= 5) {
                printLargeDepositors(result);
                System.exit(0);
            }
        }

        searchByLastNameHelper(h.right, last_name, result);
    }

    private void printLargeDepositors(List<LargeDepositor> list) {
        for (LargeDepositor depositor : list) {
            System.out.println(depositor);
        }
    }

    @Override
    public void remove(int AFM) {
        root = removeHelper(root, AFM);
    }

    private TreeNode removeHelper(TreeNode h, int AFM) {//βοηθητικη μεθοδος για την remove
        if (h == null) {
            System.out.println("LargeDepositor with AFM " + AFM + " not found.");
            return null;
        }

        if (AFM < h.item.key()) {
            h.left = removeHelper(h.left, AFM);
        } else if (AFM > h.item.key()) {
            h.right = removeHelper(h.right, AFM);
        } else {
            h = joinLR(h.left, h.right);
        }

        h.N = 1 + size(h.left) + size(h.right);
        return h;
    }


    private TreeNode joinLR(TreeNode a, TreeNode b) {
        int N = size(a) + size(b);
        if (a == null) return b;
        if (b == null) return a;

        if (Math.random() * N < 1.0 * size(a)) {
            a.right = joinLR(a.right, b);
            return a;
        } else {
            b.left = joinLR(a, b.left);
            return b;
        }
    }


    @Override
    public double getMeanSavings() {
        double[] sum = {0};
        int[] count = {0};
        calculateMeanSavings(root, sum, count);
        return (count[0] == 0) ? 0 : sum[0] / count[0];
    }

 
    private void calculateMeanSavings(TreeNode h, double[] sum, int[] count) {
        if (h == null)
            return;

        calculateMeanSavings(h.left, sum, count);
        sum[0] += h.item.getSavings();
        count[0]++;
        calculateMeanSavings(h.right, sum, count);
    }



   public void printΤopLargeDepositors(int k) {
		PQ priorityQueue = new PQ();

		printTopLargeDepositorsHelper(root, priorityQueue, k);

		
		for (int i = 0; i < k; i++) {
			LargeDepositor ld = priorityQueue.getMin();
			if (ld != null) {
				System.out.println(ld);
			}
		}
	}



    private void printTopLargeDepositorsHelper(TreeNode h, PQ priorityQueue, int k) {//βοηθητικη μεθοδος για την printTopLargeDepositors
    if (h == null)
        return;

    printTopLargeDepositorsHelper(h.left, priorityQueue, k);

    if (priorityQueue.size() < k) {
        priorityQueue.insert(h.item);
    } else if (priorityQueue.getMin().getSavings() - priorityQueue.getMin().getTaxedIncome() < h.item.getSavings() - h.item.getTaxedIncome()) {
        priorityQueue.getMin();
        priorityQueue.insert(h.item);
    }

    printTopLargeDepositorsHelper(h.right, priorityQueue, k);
	}



    @Override
    public void printByAFM() {
        printByAFMHelper(root);
    }


    private void printByAFMHelper(TreeNode h) {//βοηθητικη μεθοδος για την printByAFMHelper
        if (h == null)
            return;

        printByAFMHelper(h.left);
        System.out.println(h.item);
        printByAFMHelper(h.right);
    }

    

    public static void main(String[] args) {
        RandomizedBST bst = new RandomizedBST();
        Scanner scanner = new Scanner(System.in);
    
        while (true) {
            System.out.println("1. Insert LargeDepositor");
            System.out.println("2. Load from file");
            System.out.println("3. Update Savings");
            System.out.println("4. Search by AFM");
            System.out.println("5. Search by Last Name");
            System.out.println("6. Remove LargeDepositor");
            System.out.println("7. Get Mean Savings");
            System.out.println("8. Print Top LargeDepositors");
            System.out.println("9. Print by AFM");
            System.out.println("0. Exit");
            System.out.print("Enter your choice: ");
    
            int choice = scanner.nextInt();
            scanner.nextLine(); 
    
            switch (choice) {
                case 1:
                    System.out.print("Enter AFM: ");
                    int afm = scanner.nextInt();
                    System.out.print("Enter First Name: ");
                    String firstName = scanner.next();
                    System.out.print("Enter Last Name: ");
                    String lastName = scanner.next();
                    System.out.print("Enter Savings: ");
                    double savings = scanner.nextDouble();
                    System.out.print("Enter taxedIncome: ");
                    double taxedIncome = scanner.nextDouble();
    
                    bst.insert(new LargeDepositor(afm,firstName, lastName, savings,taxedIncome ));
                    System.out.println("LargeDepositor inserted successfully.\n");
                    break;
                case 2:
                    System.out.print("Enter filename: ");
                    String filename = scanner.next();
                    try {
                        bst.load(filename);
                        System.out.println("Data loaded successfully.");
                    } catch (FileNotFoundException e) {
                        System.out.println("File not found. Please check the filename and try again.");
                    }
                    break;
                case 3:
                    System.out.print("Enter AFM: ");
                    int afmToUpdate = scanner.nextInt();
                    System.out.print("Enter new Savings: ");
                    double newSavings = scanner.nextDouble();
    
                    bst.updateSavings(afmToUpdate, newSavings);
                    System.out.println("Savings updated successfully.");
                    break;
                case 4:
                    System.out.print("Enter AFM: ");
                    int afmToSearch = scanner.nextInt();
                    LargeDepositor result = bst.searchByAFM(afmToSearch);
    
                    if (result != null) {
                        System.out.println("LargeDepositor found: " + result);
                    } else {
                        System.out.println("LargeDepositor not found.");
                    }
                    break;
                case 5:
                    System.out.print("Enter Last Name: ");
                    String lastNameToSearch = scanner.next();
                    List<LargeDepositor> resultList = bst.searchByLastName(lastNameToSearch);
    
                    if (!resultList.isEmpty()) {
                        System.out.println("Matching LargeDepositors:");
                        bst.printLargeDepositors(resultList);
                    } else {
                        System.out.println("No matching LargeDepositors found.");
                    }
                    break;
                case 6:
                    System.out.print("Enter AFM: ");
                    int afmToRemove = scanner.nextInt();
                    bst.remove(afmToRemove);
                    System.out.println("LargeDepositor removed successfully.");
                    break;
                case 7:
                    double meanSavings = bst.getMeanSavings();
                    System.out.println("Mean Savings: " + meanSavings);
                    break;
                case 8:
                    System.out.print("Enter k: ");
                    int k = scanner.nextInt();
                    System.out.println("Top " + k + " LargeDepositors:");
                    bst.printΤopLargeDepositors(k);
                    break;
                case 9:
                    System.out.println("LargeDepositors sorted by AFM:");
                    bst.printByAFM();
                    break;
                case 0:
                    System.out.println("Exiting program.");
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    
}
