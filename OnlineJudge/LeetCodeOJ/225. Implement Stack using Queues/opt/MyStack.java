class MyStack {
    // Push element x onto stack.
    private Queue Q = new LinkedList();
    public void push(int x) {
        Queue q = new LinkedList();
        q.add(x);
        q.add(Q);
        Q = q;
    }

    // Removes the element on top of the stack.
    public void pop() {
        Q.poll();
        Q = (Queue) Q.poll();
    }

    // Get the top element.
    public int top() {
        return (Integer) Q.peek();
    }

    // Return whether the stack is empty.
    public boolean empty() {
        return Q.isEmpty();
    }
}
