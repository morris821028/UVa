#include <stdio.h>
#include <stack>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
int priority_op(char c) {
    switch(c) {
        case '(':return 0;
        case '+': case '-':return 1;
        case '*': case '/':return 2;
    }
    return -1;
}
void toPostfix(char infix[], char buffer[]) {
    int len = (int) strlen(infix);
    char *ptr = buffer;
    stack<char> op;
    *ptr = '\0';
    for (int i = 0; i < len; i++) {
        if (infix[i] == ' ')	continue;
        if (isdigit(infix[i]) || isalpha(infix[i])) {
            while (isdigit(infix[i]) || isalpha(infix[i])) {
//                sprintf(ptr, "%c", infix[i]), i++;
                i++;
                while (*ptr)    ptr++;
            }
            sprintf(ptr, "x");
            while (*ptr)    ptr++;
            i--;
        } else {
            if (infix[i] == ')') {
                while (!op.empty() && op.top() != '(') {
                    sprintf(ptr, "%c", op.top()), op.pop();
                    while (*ptr) ptr++;
                }
                op.pop();
            } else {
                if (infix[i] != '(') {
                    while (!op.empty() && priority_op(op.top()) >= priority_op(infix[i])) {
                        sprintf(ptr, "%c", op.top()), op.pop();
                        while (*ptr) ptr++;
                    }
                }
                op.push(infix[i]);
            }
        }
    }
    while (!op.empty()) {
        sprintf(ptr, "%c", op.top()), op.pop();
        while (*ptr) ptr++;
    }
}
vector<int> buildBST(char buf[]) {
    stack<int> stk;
    vector<int> hash;
    int a, b, c;
    for (int i = 0; buf[i]; i++) {
        int ha = 63689, hb = 378551;
        switch (buf[i]) {
            case '+': case '-': case '*': case '/':
                b = stk.top(), stk.pop();   // right
                a = stk.top(), stk.pop();   // left
                c = 0;
                c = c*ha + a, ha *= hb;
                c = c*ha + b, ha *= hb;
                c = c*ha + 1;
                stk.push(c);
                hash.push_back(c);
                break;
            case 'x':
                stk.push(1);
                hash.push_back(1);
                break;
            default:
                break;
        }
    }
    return hash;
}
char s[1048576], buf[1048576];
int main() {
    while (scanf("%s", s) == 1) {
        toPostfix(s, buf);
        vector<int> a = buildBST(buf);
        scanf("%s", s);
        toPostfix(s, buf);
        vector<int> b = buildBST(buf);
        
        int ret = 0, final = a.back();
        for (int i = 0; i < b.size(); i++)
            ret += b[i] == final;
        printf("%d\n", ret);
    }
    return 0;
}