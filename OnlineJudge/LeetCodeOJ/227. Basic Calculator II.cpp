class Solution {
public:
    int priority_op(char c) {
        switch(c) {
            case '(':return 0;
            case '+': case '-':return 1;
            case '*': case '/':return 2;
        }
        return -1;
    }
    int isOper(char c) {
        switch(c) {
            case '(':return 1;
            case '+': case '-':return 1;
            case '*': case '/':return 1;
        }
        return 0;
    }
    string infix2postfix(const char infix[]) {
        int len = strlen(infix);
        string ret = "";
        stack<char> op;
        for(int i = 0; i < len; i++) {
        	if (infix[i] == ' ')	continue;
            if(infix[i] >= '0' && infix[i] <= '9') {
                while (infix[i] >= '0' && infix[i] <= '9') {
                	ret += infix[i], i++;
            	}
            	ret += " ";
            	i--;
            }else {
                if(infix[i] == ')') {
                    while(!op.empty() && op.top() != '(')
                        ret += (char) op.top(), ret += " ", op.pop();
                    op.pop();
                } else {
                    if(infix[i] != '(') {
                        while(!op.empty() && priority_op(op.top()) >= priority_op(infix[i]))
                            ret += (char) op.top(), ret += " ", op.pop();
                    }
                    op.push(infix[i]);
                }
            }
        }
        while(!op.empty()) {
            ret += (char) op.top();
            ret += " ", op.pop();
        }
        return ret;
    }
    int calcPostfix(string postfix) {
        stringstream sin(postfix);
        string token;
        stack<int> stk;
        int a, b, c;
        while (sin >> token) {
        	if (token.length() == 1 && isOper(token[0])) {
                b = stk.top(), stk.pop();
                a = stk.top(), stk.pop();
                switch(token[0]) {
                    case '+': a = a+b;break;
                    case '-': a = a-b;break;
                    case '*': a = a*b;break;
                    case '/': a = a/b;break;
                }
                stk.push(a);
        	} else {
        		stringstream cc(token);
        		cc >> c;
        		stk.push(c);
        	}
        }
        return stk.top();
    }
    int calculate(string s) {
        string postfix = infix2postfix(s.c_str());
        int ret = calcPostfix(postfix);
        return ret;
    }
};
