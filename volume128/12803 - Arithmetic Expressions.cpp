#include <stdio.h>
#include <stack>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;
int priority_op(char c) {
    switch(c) {
        case '(':return 0;
        case '+': case '-':return 1;
        case '*': case '/':return 2;
    }
    return -1;
}
void trans(char infix[], char buffer[]) {
    int len = strlen(infix);
    char *ptr = buffer;
    stack<char> op;
    *ptr = '\0';
    for(int i = 0; i < len; i++) {
    	if (infix[i] == ' ')	continue;
        if(infix[i] >= '0' && infix[i] <= '9' || 
			(infix[i] == '-' && infix[i+1] >= '0' && infix[i+1] <= '9')) {
			while (infix[i] >= '0' && infix[i] <= '9' || 
				(infix[i] == '-' && infix[i+1] >= '0' && infix[i+1] <= '9') || infix[i] == '.') {
            	sprintf(ptr, "%c", infix[i]), i++;
            	while(*ptr)    ptr++;
        	}
        	sprintf(ptr, " ");
            while(*ptr)    ptr++;
        	i--;
        }else {
            if(infix[i] == ')') {
                while(!op.empty() && op.top() != '(') {
                    sprintf(ptr, "%c ", op.top()), op.pop();
                    while(*ptr) ptr++;
                }
                op.pop();
            } else {
                if(infix[i] != '(')
                while(!op.empty() && priority_op(op.top()) >= priority_op(infix[i])) {
                    sprintf(ptr, "%c ", op.top()), op.pop();
                    while(*ptr) ptr++;
                }
                op.push(infix[i]);
            }
        }
    }
    while(!op.empty()) {
        sprintf(ptr, "%c ", op.top()), op.pop();
        while(*ptr) ptr++;
    }
}
int isOper(char c) {
    switch(c) {
        case '(':return 1;
        case '+': case '-':return 1;
        case '*': case '/':return 1;
    }
    return 0;
}
double calcPostfix(char postfix[]) {
	stringstream sin(postfix);
	string token;
    stack<double> stk;
    double a, b, c;
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
char infix[262144], postfix[262144];

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		gets(infix);
		trans(infix, postfix);
		printf("%.2lf\n", calcPostfix(postfix));
	}
	return 0;
}
/*
3
( 3.00 + 4.50 )
( 5.00 - ( 2.50 * 3.00 ) )
( ( 7.00 / 3.00 ) + ( 4.00 - ( 3.00 * 7.00 ) ) )
*/
