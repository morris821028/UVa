#include <stdio.h>
#include <stack>
#include <iostream>
#include <sstream>
using namespace std;
int priority(char c) {
    switch(c) {
        case '(':return 1;
        case '+':return 2;
        case '-':return 2;
        case '*':return 3;
        case '/':return 3;
    }
    puts("error");
    return -1; // error state
}
string infix2postfix(string infix) {
    string postfix = "";
    int i, j, len = infix.length();
    stack<char> opStk;
    for(i = 0; i < len; i++) {
        if(infix[i] == ' ')
            continue;
#define isVar(x) (x == 'x' || (x >= '0' && x <= '9'))
        if(isVar(infix[i])) { // isVar
            while(i < len && isVar(infix[i])) {
                postfix += infix[i];
                i++;
            }
            i--;
            postfix += ' ';
        } else { // operator | ( | )
            if(infix[i] == ')') {
                while(!opStk.empty()) {
                    if(opStk.top() == '(') {
                       opStk.pop();
                       break;
                    }
                    postfix += opStk.top();
                    postfix += ' ';
                    opStk.pop();
                }
            } else {
                while(!opStk.empty() && infix[i] != '(') {
                    if(opStk.top() == '(')
                        break;
                    if(priority(opStk.top()) < priority(infix[i]))
                        break;
                    postfix += opStk.top();
                    postfix += ' ';
                    opStk.pop();
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
struct Var {
    int i, j;
};
Var calcPostfix(string postfix) {
    stack<Var> stk;
    stringstream sin(postfix);
    string token;
    Var a, b, c;
    while(sin >> token) {
        switch(token[0]) {
            case '+':case '-':case '*':case '/':
                if(!stk.empty())
                    b = stk.top(), stk.pop();
                if(!stk.empty())
                    a = stk.top(), stk.pop();
                // only linear equation
                //cout << a.i << " " << a.j << endl;
                //cout << token << endl;
                //cout << b.i << " " << b.j << endl;
                if(token == "+")
                    c.i = a.i+b.i, c.j = a.j+b.j;
                if(token == "-")
                    c.i = a.i-b.i, c.j = a.j-b.j;
                if(token == "*")
                    c.i = a.i*b.i, c.j = a.i*b.j+a.j*b.i;
                //cout << "=" << c.i << " " << c.j << endl;
                stk.push(c);
                break;
            default:
                stringstream str2int(token);
                if(token[0] == 'x') {
                    a.j = 1, a.i = 0;
                } else {
                    str2int >> a.i;
                    a.j = 0;
                }
                stk.push(a);
        }
    }
    return stk.top();
}
int main() {
    string line;
    int cases = 0;
    int pos;
    while(getline(cin, line)) {
        if(cases)   puts("");
        printf("Equation #%d\n", ++cases);
        for(pos = 0; line[pos] != '='; pos++);
        string left, right, postLeft, postRight;
        left = line.substr(0, pos);
        right = line.substr(pos+1);
        postLeft = infix2postfix(left);
        postRight = infix2postfix(right);
        Var rL = calcPostfix(postLeft);
        Var rR = calcPostfix(postRight);
        //cout << postLeft << "|"<< endl;
        //cout << rL.i << " " << rL.j << endl;
        if(rL.j-rR.j) {
            printf("x = %.6lf\n", (double)(rR.i-rL.i)/(rL.j-rR.j));
        } else {
            if(rR.i == rL.i)
                puts("Infinitely many solutions.");
            else
                puts("No solution.");
        }
    }
    return 0;
}
