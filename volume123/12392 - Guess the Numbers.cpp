#include <iostream>
#include <sstream> // stringstream
#include <ctype.h> // isdigit()
#include <stdio.h>
#include <algorithm>
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
        if(isdigit(infix[i]) || isalpha(infix[i])) { // cut number
            while(i < len && (isdigit(infix[i]) || isalpha(infix[i]))) {
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
int assign_val[26];
int calcPostfix(string postfix) {
    STACK<int> stk;
    stringstream sin(postfix);
    string token;
    int a, b;
    while(sin >> token) {
        switch(token[0]) {
            case '+': case '-': case '*':
                b = stk.top(), stk.pop();
                a = stk.top(), stk.pop();
                if(token == "+")
                    stk.push(a+b);
                if(token == "-")
                    stk.push(a-b);
                if(token == "*")
                    stk.push(a*b);
                break;
            default:
                a = assign_val[token[0]-'a'];
                stk.push(a);
        }
    }
    return stk.top();
}
//</calc postfix>
int main() {
    int n, m, i, j, v[10];
    string infix, postfix;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", &v[i]);
        scanf("%d", &m);
        while(getchar() != '\n');
        getline(cin, infix);
        postfix = infix2postfix(infix);
        int unknown_val[26] = {}, postfix_len = postfix.length();
        for(i = 0; i < postfix_len; i++) {
            if(isalpha(postfix[i])) {
                unknown_val[postfix[i]-'a'] = 1;
            }
        }
        for(i = 0, j = 0; i < 26; i++) {
            if(unknown_val[i])
                unknown_val[j++] = i;
        }
        int flag = 0;
        do {
            for(i = 0; i < n; i++)
                assign_val[unknown_val[i]] = v[i];
            long long calc_ans = calcPostfix(postfix);
            if(calc_ans == m)
                flag = 1;
        } while(!flag && next_permutation(unknown_val, unknown_val+n));
        puts(flag ? "YES" : "NO");
    }
    return 0;
}
