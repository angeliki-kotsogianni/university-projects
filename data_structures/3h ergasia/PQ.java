public class PQ implements PQInterface{ //τροποποιημενος κωδικας απο 2η εργασια
	private LargeDepositor[] heap;
    private int maxSize;
    private int size;
    private int[] idToIndex;

    public PQ() {
        maxSize = 100;
        heap = new LargeDepositor[maxSize];
        size = 0;
        idToIndex = new int[maxSize];
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public int size() {
        return size;
    }

    public void insert(LargeDepositor x) {
        if (size == maxSize * 0.75) {
            resize(maxSize * 2);
        }

        size++;
        int index = size;
        heap[index] = x;
        idToIndex[index] = x.key();

        swim(index);
    }

    public LargeDepositor min() {
        return heap[1];
    }

    public LargeDepositor getMin() {
        LargeDepositor min = heap[1];
        swap(1, size);
        heap[size] = null;
        size--;
        sink(1);
        return min;
    }

    public LargeDepositor remove(int id) {
        if (isEmpty()) {
            return null;
        }

        int index = idToIndex[id];
        LargeDepositor ldremoved = heap[index];
        heap[index] = heap[size];
        heap[size] = null;
        size--;

        idToIndex[index] = heap[index].key();

        sink(index);

        return ldremoved;
    }

    private void resize(int newMax) {
        LargeDepositor[] newHeap = new LargeDepositor[newMax];
        int[] newIdToIndex = new int[newMax];

        for (int i = 1; i <= size; i++) {
            newHeap[i] = heap[i];
            newIdToIndex[i] = heap[i].key();
        }

        heap = newHeap;
        idToIndex = newIdToIndex;
        maxSize = newMax;
    }

    private void swim(int k) {
        while (k > 1 && heap[k].compareTo(heap[k / 2]) < 0) {
            swap(k, k / 2);
            k = k / 2;
        }
    }

    private void sink(int k) {
        while (2 * k <= size) {
            int j = 2 * k;
            if (j < size && heap[j].compareTo(heap[j + 1]) > 0) {
                j++;
            }
            if (heap[k].compareTo(heap[j]) <= 0) {
                break;
            }
            swap(k, j);
            k = j;
        }
    }

    private void swap(int i, int j) {
        LargeDepositor temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;

        idToIndex[i] = heap[i].key();
        idToIndex[j] = heap[j].key();
    }

}
