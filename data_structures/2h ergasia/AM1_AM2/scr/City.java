public class City implements CityInterface,Comparable<City> {
	
	private int id;
	private String name;
	private int population;
	private int influenzaCases;
	
	City(){
	}
	
	City(int id, String name, int population, int influenzaCases){
		this.id = id;
		this.name = name;
		this.population = population;
		this.influenzaCases = influenzaCases;
	}

    @Override
    public int getID() {
        return id;
    }

    @Override
    public void setID(int id) {
		this.id = id;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public void setName(String name) {
		this.name = name;
    }

    @Override
    public int getPopulation() {
        return population;
    }

    @Override
    public void setPopulation(int population) {
		this.population = population;
    }

    @Override
    public int getInfluenzaCases() {
        return influenzaCases;
    }

    @Override
    public void setInfluenzaCases(int influenzaCases) {
		this.influenzaCases = influenzaCases;
    }
	
	public int compareTo(City another_city) {
		double density1 = calculateDensity(this.population, this.influenzaCases);
        double density2 = calculateDensity(another_city.population, another_city.influenzaCases);
		
        if (density1 != density2) {
            return Double.compare(density1, density2);
        }
		
        int name_compare = this.name.compareTo(another_city.name);
        if (name_compare != 0) {
            return name_compare;
        }

        return Integer.compare(this.id, another_city.id);
    }

    private double calculateDensity(int population, int influenzaCases) {
        return ((double) influenzaCases / population) * 50000;
    }
}
