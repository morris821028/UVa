class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> stk;
    int mn;
    MinStack() {
    }
    
    void push(int x) {
        if (stk.size() == 0 || x <= mn) {
            stk.push(mn);
            mn = x;
        }
        stk.push(x);
    }
    
    void pop() {
        if (top() == mn) {
            stk.pop();
            mn = top(), stk.pop();
        } else {
            stk.pop();
        }
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return mn;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
