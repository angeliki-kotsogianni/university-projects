public class Node<T> {
	
    protected T data;
    protected Node<T> next;
    protected Node<T> prev;


    /**
     * Constructor. Sets data
     *
     * @param item the data stored
     * @return
     */
    Node(T data) {
        this.data = data;
        this.next = null;
        this.prev = null;
    }
	
	public T getData(){
		return data;
	}
	
	public Node<T> getNext(){
		return next;
	}
	
	public void setNext(Node<T> next) {
        this.next = next;
    }
	
	public Node<T> getPrev(){
		return prev;
	}
	
	public void setPrev(Node<T> prev) {
        this.prev = prev;
    }
	
}
