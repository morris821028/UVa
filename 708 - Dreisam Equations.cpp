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
//<parse infix>
int priority(char c) {
    switch(c) {
        case '(':return 1;
        case '+':return 2;
        case '-':return 2;
        case '*':return 2;
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
long long calcPostfix(string postfix) {
    STACK<long long> stk;
    stringstream sin(postfix), str2int;
    string token;
    long long a, b, neg;
    while(sin >> token) {
        switch(token[0]) {
            case '+': case '-': case '*':
                if(stk.size() == 0)
                    while(1);
                b = stk.top(), stk.pop();
                if(stk.size() == 0)
                    while(1);
                a = stk.top(), stk.pop();
                neg = 1; // exist neg number
                if(token == "+")
                    stk.push(a+b), neg = 0;
                if(token == "-")
                    stk.push(a-b), neg = 0;
                if(token == "*")
                    stk.push(a*b), neg = 0;
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
        while(1);
    return stk.top();
}
//</calc postfix>
string R[100], postfix;
long long L, flag;
void dfs(int idx, int n, string infix) {
    if(flag)    return;
    if(idx == n) {
        //postfix = infix2postfix(infix);
        //long long res = calcPostfix(postfix);
        //if(res == L) {
         //   flag = 1;
         //   printf("%lld=%s\n", L, infix.c_str());
        //}
        return;
    }
    dfs(idx+1, n, infix + "+" + R[idx]);
    dfs(idx+1, n, infix + "-" + R[idx]);
    dfs(idx+1, n, infix + "*" + R[idx]);
}
int main() {
    int cases = 0;
    string cmd;
    while(getline(cin, cmd)) {
        if(cmd == "0")  break;
        printf("Equation #%d:\n", ++cases);
        stringstream sin(cmd);
        sin >> L;
        sin >> R[0];
        int n = 1;
        //while(sin >> R[n])
          //  n++;
        flag = 0;
        dfs(1, n, R[0]);
        if(!flag)   puts("Impossible.");
        puts("");
    }
    return 0;
}
