class LargeDepositor {
    private int AFM;
    private String firstName; 
    private String lastName; 
    private double savings; 
    private double taxedIncome;

    public LargeDepositor(int AFM, String firstName, String lastName, double savings, double taxedIncome) {
        this.AFM = AFM;
        this.firstName = firstName;
        this.lastName = lastName;
        this.savings = savings;
        this.taxedIncome = taxedIncome;
    }

    public int key() {
        return AFM;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public double getSavings() {
        return savings;
    }

    public double getTaxedIncome() {
        return taxedIncome;
    }

    public void setSavings(double savings) {
        this.savings = savings;
    }

    @Override
    public String toString() {
        return "LargeDepositor{" +
                "AFM=" + AFM +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", savings=" + savings +
                ", taxedIncome=" + taxedIncome +
                '}';
    }
}
