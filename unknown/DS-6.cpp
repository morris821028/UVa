#include <iostream> // author: morris
#include <sstream> // stringstream
#include <ctype.h> // isdigit()
using namespace std;
//<stack template>
template <typename T>
struct Node {
    T d;
    Node *prev;
};
template <class T>
class STACK { // linked list implements stack
    public:
        STACK() {
            idx = NULL;
            SIZE = 0;
        }
        T top() {
            T cpy = idx->d;
            return cpy;
        }
        void pop() {
            Node<T> *tmp;
            tmp = idx;
            idx = idx->prev;
            delete tmp;
            SIZE--;
        }
        void push(T item) {
            Node<T> *nd = new Node<T>;
            nd->d = item;
            nd->prev = idx;
            idx = nd;
            SIZE++;
        }
        bool empty() {
            return idx == NULL;
        }
        int size() {
            return SIZE;
        }
    private:
        Node<T> *idx;
        int SIZE;
};
//</stack template>
//<parse infix>
int priority(char c) {
    switch(c) {
        case '(':return 1;
        case '+':return 2;
        case '-':return 2;
        case '*':return 3;
        case '/':return 3;
    }
    return -1; // error state
}
string infix2postfix(string infix) {
    string postfix = "";
    int i, j, len = infix.length();
    STACK<char> opStk; // save operator, not number
    for(i = 0; i < len; i++) {
        if(infix[i] == ' ')
            continue;
        if(isdigit(infix[i])) { // cut number
            while(i < len && isdigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            i--; // because for loop i++
            postfix += ' ';
        } else { // operator or '(' or ')'
            if(infix[i] == ')') {
                while(opStk.top() != '(') {
                    postfix += opStk.top();
                    postfix += ' ';
                    opStk.pop();
                }
                opStk.pop(); // pop '('
            } else {
                while(!opStk.empty() && infix[i] != '(') {
                    if(opStk.top() != '(') {
                        if(priority(opStk.top()) >= priority(infix[i])) {
                            postfix += opStk.top();
                            postfix += ' ';
                            opStk.pop();
                        } else
                            break;
                    } else
                        break;
                }
                opStk.push(infix[i]);
            }
        }
    }
    while(!opStk.empty()) {
        postfix += opStk.top();
        postfix += ' ';
        opStk.pop();
    }
    return postfix;
}
//</parse infix>
//<calc postfix>
double calcPostfix(string postfix) {
    STACK<double> stk;
    stringstream sin(postfix), str2int;
    string token;
    double a, b, neg;
    while(sin >> token) {
        switch(token[0]) {
            case '+': case '-': case '*': case '/': case '%':
                b = stk.top(), stk.pop();
                a = stk.top(), stk.pop();
                neg = 1; // exist neg number
                if(token == "+")
                    stk.push(a+b), neg = 0;
                if(token == "-")
                    stk.push(a-b), neg = 0;
                if(token == "*")
                    stk.push(a*b), neg = 0;
                if(token == "/")
                    stk.push(a/b), neg = 0;
                if(neg == 0)
                    break;
            default:
                str2int.clear();
                str2int << token;
                str2int >> a;
                stk.push(a);
        }
    }
    if(stk.size() != 1)
        cout << "Error" << endl;
    return stk.top();
}
//</calc postfix>
int main() {
    string infix, postfix;
    while(cout << "Please enter an infix expression: ",
          getline(cin, infix)) {// EOF window ctrl+z+enter, linux ctrl+d
        postfix = infix2postfix(infix);
        cout << "postfix expression: " << postfix << endl;
        cout << "calculate result: " << calcPostfix(postfix) << endl;
    }
    return 0;
}
