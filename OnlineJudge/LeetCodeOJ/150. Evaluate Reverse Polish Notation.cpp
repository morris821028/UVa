class Solution {
public:
    int isoperator(string e) {
        if (e == "+")
            return '+';
        if (e == "-")
            return '-';
        if (e == "*")
            return '*';
        if (e == "/")
            return '/';
        return 0;
    }
    int evalRPN(vector<string>& tokens) {
        if (tokens.size() == 0)
            return 0;
        stack<int> stk;
        for (auto e : tokens) {
            int t = isoperator(e);
            if (t == 0) {
                int x;
                sscanf(e.c_str(), "%d", &x);
                stk.push(x);
            } else {
                int a, b;
                b = stk.top(), stk.pop();
                a = stk.top(), stk.pop();
                switch(t) {
                    case '+': stk.push(a+b);
                        break;
                    case '-': stk.push(a-b);
                        break;
                    case '*': stk.push(a*b);
                        break;
                    case '/': stk.push(a/b);
                        break;
                }
            }
        }
        return stk.top();
    }
};
