#include <iostream>
#include <sstream> // stringstream
#include <ctype.h> // isdigit()
#include <stdio.h>
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
int error;
//<parse infix>
int priority(char c) {
    switch(c) {
        case '(':return 1;
        case '+':return 2;
        case '-':return 2;
        case '*':return 3;
    }
    error = 1;
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
                while(opStk.size() && opStk.top() != '(') {
                    postfix += opStk.top();
                    postfix += ' ';
                    opStk.pop();
                }
                if(opStk.size())
                    opStk.pop(); // pop '('
                else    error = 1;
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
void calcPostfix(string postfix) {
    STACK<int> stk;
    stringstream sin(postfix), str2int;
    string token;
    int a, b;
    while(sin >> token) {
        switch(token[0]) {
            case '+': case '*':
                if(stk.size() == 0) {error = 1;return;}
                b = stk.top(), stk.pop();
                if(stk.size() == 0) {error = 1;return;}
                a = stk.top(), stk.pop();
                if(token == "+")
                    stk.push(a+b);
                else if(token == "*")
                    stk.push(a*b);
                else
                    {error = 1;return;}
                break;
            default:
                str2int.clear();
                str2int << token;
                if(str2int >> a) {}
                else    {error = 1;return;}
                stk.push(a);
        }
    }
    if(stk.size() != 1) {error = 1;return;}
    printf("%d\n", stk.top());
}
//</calc postfix>
int main() {
    string infix, postfix;
    getline(cin, infix);
    while(getline(cin, infix)) {
        error = 0;
        postfix = infix2postfix(infix);
        //cout << postfix << endl;
        if(!error)
            calcPostfix(postfix);
        if(error)
            puts("ERROR");
    }
    return 0;
}
