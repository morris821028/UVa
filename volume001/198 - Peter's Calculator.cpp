#include <stdio.h>
#include <stack>
#include <string.h>
#include <algorithm>
#include <ctype.h>
#include <iostream>
#include <sstream>
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
int isoperator(char c) {
    switch(c) {
        case '(':case ')':case '+': case '-':case '*': case '/':return 1;
    }
    return 0;
}
int isvariable(string token) {
	return isalpha(token[0]);
}
void trans(const char *infix, char buffer[]) {
    int len = strlen(infix), prevOp = 1;
    char *ptr = buffer;
    stack<char> op;
    *ptr = '\0';
    for(int i = 0; i < len; i++) {
        if(isalpha(infix[i]) || isdigit(infix[i]) 
			|| (infix[i] == '-' && isdigit(infix[i+1]) && prevOp)) {
			prevOp = 0;
        	sprintf(ptr, "%c", infix[i]), i++;
        	while(*ptr)    ptr++;
			while(isalpha(infix[i]) || isdigit(infix[i])) {
            	sprintf(ptr, "%c", infix[i]), i++;
            	while(*ptr)    ptr++;
            }
            sprintf(ptr, " "), i--;
            while(*ptr)		ptr++;
        } else {
        	prevOp = 0;
            if(infix[i] == ')') {
                while(!op.empty() && op.top() != '(') {
                    sprintf(ptr, "%c ", op.top()), op.pop();
                    while(*ptr) ptr++;
                }
                op.pop();
            } else {
                if(infix[i] != '(') {
	                while(!op.empty() && priority_op(op.top()) >= priority_op(infix[i])) {
	                    sprintf(ptr, "%c ", op.top()), op.pop();
	                    while(*ptr) ptr++;
	                }
            	}
	        	prevOp = 1;
                op.push(infix[i]);
            }
        }
    }
    while(!op.empty()) {
        sprintf(ptr, "%c ", op.top()), op.pop();
        while(*ptr) ptr++;
    }
}
void trimWhiteSpace(char s[]) {
	int j = 0;
	for(int i = 0; s[i]; i++)
		if(!isspace(s[i]))
			s[j++] = s[i];
	s[j] = '\0';
}
map<string, string> VAL_exp;
map<string, int>	VAL_val;
map<string, int>	VAL_stk;
int error_FLAG;
int calcPostfix(const char* postfix);
int getValue(string VAL_name) {
    if(!isvariable(VAL_name)) {
    	stringstream scin(VAL_name);
    	int value;
    	scin >> value;
    	return value;
    }
	if(VAL_exp.find(VAL_name) == VAL_exp.end() || VAL_stk[VAL_name]) {
		error_FLAG = 1;
		return 0;
	}
	if(VAL_val.find(VAL_name) == VAL_val.end()) {
		VAL_stk[VAL_name] = 1;
//		cout << "solving " << VAL_name << ", " << VAL_exp[VAL_name] << endl; 
		VAL_val[VAL_name] = calcPostfix(VAL_exp[VAL_name].c_str());
//		cout << "solved " << VAL_name << ", val = " << VAL_val[VAL_name] << endl;
		VAL_stk[VAL_name] = 0;
	}
	return VAL_val[VAL_name];
}
int calcPostfix(const char* postfix) {
	stringstream 	scin(postfix);
    stack<int> 		stk;
	string			token;
    int 			a, b;
    
    while(scin >> token) {
    	if(token.length() == 1 && isoperator(token[0])) {
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
    		stk.push(getValue(token));
    	}
    	if(error_FLAG)	return 0;
    }
    return stk.top();
}
void printVal(string valName) {
	error_FLAG = 0;
	VAL_val.clear();
	VAL_stk.clear();
	int val = getValue(valName);
	if(error_FLAG)
		puts("UNDEF");
	else
		printf("%d\n", val);
}
int main() {
//	freopen("input.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	string 	LHS, RHS;
	int 	pos;
	char 	postfix[32767], lines[32767];
	
    while(gets(lines)) {
    	trimWhiteSpace(lines);
    	string str(lines);
    	if(str.find(":=") != string::npos) {
    		pos = str.find(":=");
    		LHS = str.substr(0, pos);
    		RHS = str.substr(pos + 2);
    		trans(RHS.c_str(), postfix);
    		VAL_exp[LHS] = postfix;
    	} else if(str.find("PRINT") != string::npos) {
    		pos = str.find("PRINT");
    		RHS = str.substr(pos + 5);
    		printVal(RHS);
    	} else if(str.find("RESET") != string::npos) {
    		VAL_exp.clear();
    	}
    }
    return 0;
}
