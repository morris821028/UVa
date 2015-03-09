#include <iostream>
#include <sstream> // stringstream
#include <ctype.h> // isdigit()
#include <stdio.h>
#include <stdlib.h>
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
        case '^':return 4;// please ignore mod
    }
    puts("error");
    return -1; // error state
}
string infix2postfix(string infix) {
    string postfix = "";
    int i, j, len = infix.length();
    STACK<char> opStk; // save operator, not number
    for(i = 0; i < len; i++) {
        if(infix[i] == ' ')
            continue;
        if(isdigit(infix[i]) || infix[i] == 'a') { // cut number
            while(i < len && (isdigit(infix[i]) || infix[i] == 'a')) {
                postfix += infix[i];
                i++;
            }
            i--; // because for loop i++
            postfix += ' ';
        } else { // operator or '(' or ')'
            if(infix[i] == ')') {
                while(!opStk.empty() && opStk.top() != '(') {
                    postfix += opStk.top();
                    postfix += ' ';
                    opStk.pop();
                }
                if(!opStk.empty())
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
long long mpow(long long x, long long y) {
    if(!y)  return 1;
    if(y&1) return x*mpow(x*x, y>>1);
    return mpow(x*x, y>>1);
}
long long calcPostfix(string postfix, long long x) {
    //cout << postfix << endl;
    STACK<long long> stk;
    stringstream sin(postfix), str2int;
    string token;
    long long a, b;
    while(sin >> token) {
        switch(token[0]) {
            case '+': case '-': case '*': case '^':
                b = stk.top(), stk.pop();
                a = stk.top(), stk.pop();
                if(token == "+")
                    stk.push(a+b);
                if(token == "-")
                    stk.push(a-b);
                if(token == "*")
                    stk.push(a*b);
                if(token == "^")
                    stk.push(mpow(a, b));
                break;
            default:
                if(token == "a") {
                    stk.push(x);
                    break;
                }
                str2int.clear();
                str2int << token;
                while(str2int >> a)
                stk.push(a);

        }
    }
    if(stk.size() != 1)
        puts("error");
    return stk.top();
}
//</calc postfix>
int main() {
    string o, s;
    int n, i, j;
    while(getline(cin, o)) {
        cin >> n;
        cin.ignore(100, '\n');
        string opost = infix2postfix(o), spost;
        long long v1, v2;
        char buf[60], bt = 0;
        for(i = 0; i < n; i++) {
            getline(cin, s);
            spost = infix2postfix(s);
            for(j = -5; j < 5; j++) {
                v1 = calcPostfix(opost, j);
                v2 = calcPostfix(spost, j);
                if(v1 != v2) {
                    break;
                }
            }
            if(j == 5)
                buf[bt++] = i+'A';
        }
        buf[bt] = '\0';
        puts(buf);
    }
    return 0;
}
