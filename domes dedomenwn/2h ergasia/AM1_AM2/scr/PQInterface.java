public interface PQInterface {
	boolean isEmpty();
	int size();
	void insert(City x);
	City min();
	City getMin();
	City remove(int id);
}