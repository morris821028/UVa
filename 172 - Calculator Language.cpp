// Wrong Answer
#include <stdio.h>
#include <stack>
#include <string.h>
#include <algorithm>
#include <ctype.h>
#include <iostream>
#include <sstream>
using namespace std;
int priority_op(char c) {
    switch(c) {
        case '(':return -1;
        case '=':return 3;
        case '+': case '-':return 1;
        case '*': case '/':return 2;
    }
    puts("ERROR");
    return -1;
}
void trans(char infix[], char buffer[]) {
    int len = strlen(infix);
    char *ptr = buffer;
    stack<char> op;
    *ptr = '\0';
    for(int i = 0; i < len; i++) {
        if(infix[i] == '_' || isdigit(infix[i]) || isalpha(infix[i])) {
        	while(infix[i] == '_' || isdigit(infix[i]) || isalpha(infix[i])) {
        		if(infix[i] == '_')
        			sprintf(ptr, "-");
        		else
            		sprintf(ptr, "%c", infix[i]);	
            	while(*ptr)    ptr++;
            	i++;
        	}
            sprintf(ptr, " ");	
            while(*ptr)    ptr++;
        	i--;
        }else {
        	if(infix[i] == ' ')	continue;
            if(infix[i] == ')') {
                while(!op.empty() && op.top() != '(') {
                    sprintf(ptr, "%c ", op.top()), op.pop();
                    while(*ptr) ptr++;
                }
                op.pop();
            } else {
                if(infix[i] != '(') {
                	if(infix[i] == '=') {
                		while(!op.empty() && priority_op(op.top()) > priority_op(infix[i])) {
                    		sprintf(ptr, "%c ", op.top()), op.pop();
                    		while(*ptr) ptr++;
                		}
                	} else {
                		while(!op.empty() && priority_op(op.top()) > priority_op(infix[i]) && op.top() != '=') {
                    		sprintf(ptr, "%c ", op.top()), op.pop();
                    		while(*ptr) ptr++;
                		}
                	}
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
int Variable[26] = {}, oldVal[26] = {};
string to_string(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}
void calcPostfix(char postfix[]) {
	stringstream	sin(postfix);
	string 			token, A, B;
    stack<string>	stk;
    while(sin >> token) {
    	if(isalpha(token[0])) {
    		stk.push(token);
    	} else if(isdigit(token[token.length() - 1])) {
    		stk.push(token);
    	} else {
			B = stk.top(), stk.pop();
            A = stk.top(), stk.pop();
            int a, b;
            if(isalpha(A[0]))
            	a = Variable[A[0] - 'A'];
            else
            	a = atoi(A.c_str());
            if(isalpha(B[0]))
            	b = Variable[B[0] - 'A'];
            else
            	b = atoi(B.c_str());
            switch(token[0]) {
            	case '+': a = a + b; stk.push(to_string(a));break;
                case '-': a = a - b; stk.push(to_string(a));break;
                case '*': a = a * b; stk.push(to_string(a));break;
                case '/': a = a / b; stk.push(to_string(a));break;
                case '=': 
                	a = b;
                	if(isalpha(A[0])) {
                		Variable[A[0] - 'A'] = a;
                		//cout << A << " -- " << a << endl;
                	}
					stk.push(to_string(a)); break;
            }
            //printf("sss = %d\n", a);
    	}
    }
}
char infix[262144], postfix[262144];
int main() {
    while(gets(infix) && infix[0] != '#') {
        trans(infix, postfix);
        
        for(int i = 0; i < 26; i++)
        	oldVal[i] = Variable[i];
        calcPostfix(postfix);
        
        int f = 0;
        for(int i = 0; i < 26; i++) {
        	if(oldVal[i] != Variable[i]) {
        		if(f)	printf(", ");
        		f = 1;
        		printf("%c = %d", i + 'A', Variable[i]);
        	}
        }
        if(f == 0)
        	puts("No change");
        else
        	puts("");
        //printf("%s\n", postfix);
    }
    return 0;
}
/*
B = (A = 1) + (A = 2) 
#

A = 1, B = 3


*/
