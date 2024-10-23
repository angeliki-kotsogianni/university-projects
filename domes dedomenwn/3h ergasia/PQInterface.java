public interface PQInterface { //τροποποιημενος κωδικας απο 2η εργασια
	boolean isEmpty();
	int size();
	void insert(LargeDepositor x);
	LargeDepositor min();
	LargeDepositor getMin();
	LargeDepositor remove(int id);
}