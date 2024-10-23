import java.io.PrintStream;
import java.util.NoSuchElementException;



public class StringDoubleendedQueueImpl<T> implements StringDoubleEndedQueue<T> {
    private Node<T> head = null;
    private Node<T> tail = null;
	private int size = 0;
	
	public StringDoubleendedQueueImpl() {
    }

    public boolean isEmpty() {
        return size == 0;
    }



    public void addFirst(T item){
        Node<T> n = new Node<>(item);

        if (isEmpty()) {
            head = n;
            tail = n;

        } else {
            n.setNext(head);
            head.setPrev(n);
            head = n;
        }
		
		size++;
    }

    public void addLast(T item) {
        Node<T> n = new Node<>(item);

        if (isEmpty()) {
            head = n;
            tail = n;
        } else {
            tail.setNext(n);
            n.setPrev(tail);
            tail = n;
        }
		
		size++;
    }

    public T removeFirst() throws NoSuchElementException {
        if (isEmpty())
            throw new NoSuchElementException();

    
            T data = head.getData();
    
            if (head.getNext() != null) {
                head = head.getNext();
                head.setPrev(null);
            } else {
                head = null;
                tail = null;
            }
			size--;
            return data;
    }

    public T removeLast() throws NoSuchElementException {
        if (isEmpty())
            throw new NoSuchElementException();

    
            T data = tail.getData();
    
            if (tail.getPrev() != null) {
                tail = tail.getPrev();
                tail.setNext(null);
            } else {
                head = null;
                tail = null;
            }
			size--;
            return data;
    }

    public T getFirst() {
        if (head == null) {
            throw new NoSuchElementException("Queue is empty");
        }
        return head.getData();
    }

    public T getLast() {
        if (tail == null) {
            throw new NoSuchElementException("Queue is empty");
        }
        return tail.getData();
    }

    public void printQueue(PrintStream stream) {
        Node<T> current = head;
        while (current != null) {
            stream.print(current.getData() + " <-> ");
            current = current.getNext();
        }
        stream.println("null");
    }

    public int size() {
        return size;
    }

}
