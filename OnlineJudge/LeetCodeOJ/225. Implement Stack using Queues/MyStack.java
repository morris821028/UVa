class MyStack {
    private Queue<Integer> qin = new LinkedList<Integer>();
    private Queue<Integer> qout = new LinkedList<Integer>();
    // Push element x onto stack.
    public void push(int x) {
        qin.add(x);
    }

    // Removes the element on top of the stack.
    public void pop() {
        if (qin.isEmpty()) {
            while (!qout.isEmpty()) {
                int x = qout.poll();
                if (!qout.isEmpty())
                    qin.add(x);
            }
        } else {
            while (!qin.isEmpty()) {
                int x = qin.poll();
                if (!qin.isEmpty())
                    qout.add(x);
            }
        }
    }

    // Get the top element.
    public int top() {
        int last = -1;
        if (qin.isEmpty()) {
            while (!qout.isEmpty()) {
                last = qout.poll();
                qin.add(last);
            }
        } else {
            while (!qin.isEmpty()) {
                last = qin.poll();
                qout.add(last);
            }
        }
        return last;
    }

    // Return whether the stack is empty.
    public boolean empty() {
        return qin.isEmpty() && qout.isEmpty();
    }
}
