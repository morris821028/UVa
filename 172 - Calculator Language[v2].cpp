// Accepted
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

struct TreeNode {
	string 	A, B, OP;
	int 	l, r;
	TreeNode(string a="", string b="", string op=""):
		A(a), B(b), OP(op) {}
};
TreeNode node[1024];
int runTree(int label) {
	string 	A = node[label].A;
	string	B = node[label].B;
	int 	a, b;
	if(node[label].OP == "LEAF") {
		if(isalpha(A[0]))
           	a = Variable[A[0] - 'A'];
        else
           	a = atoi(A.c_str());
		return a;	
	}
	b = runTree(node[label].r);
	a = runTree(node[label].l);
//	printf("%d %d\n", a, b);
	// cout << A << ", " << B << ", " << node[label].OP << endl;
	switch(node[label].OP[0]) {
    	case '+': a = a + b; break;
        case '-': a = a - b; break;
        case '*': a = a * b; break;
        case '/': a = a / b; break;
        case '=': 
        	a = b;
        	if(isalpha(A[0])) {
        		Variable[A[0] - 'A'] = a;
        		cout << A << " -- " << a << endl;
        	}
        	break;
    }
    return a;
}
void buildTree(char postfix[]) {
	
	stringstream	sin(postfix);
	string 			token, A, B;
    stack<string>	stk;
    stack<int>		nodeLabel;
    int 			treeSize = 0;
    
    while(sin >> token) {
    	if(isalpha(token[0])) {
    		stk.push(token);
    		nodeLabel.push(treeSize);
    		node[treeSize++] = TreeNode(token, "", "LEAF");
    		
    	} else if(isdigit(token[token.length() - 1])) {
    		stk.push(token);
    		nodeLabel.push(treeSize);
    		node[treeSize++] = TreeNode(token, "", "LEAF");
    	} else {
			B = stk.top(), stk.pop();
            A = stk.top(), stk.pop();
            int a, b;
            b = nodeLabel.top(), nodeLabel.pop();
            a = nodeLabel.top(), nodeLabel.pop();
            nodeLabel.push(treeSize);
            node[treeSize] = TreeNode(A, B, token);
            node[treeSize].l = a, node[treeSize].r = b;
            treeSize++;
            stk.push("INNER");
    	}
    }
    runTree(nodeLabel.top());
}
char infix[262144], postfix[262144];
int main() {
    while(gets(infix) && infix[0] != '#') {
        trans(infix, postfix);
        
        for(int i = 0; i < 26; i++)
        	oldVal[i] = Variable[i];
        	
        buildTree(postfix);
        
        int f = 0;
        for(int i = 0; i < 26; i++) {
        	if(oldVal[i] != Variable[i]) {
        		if(f)	printf(", ");
        		f = 1;
        		printf("%c = %d", i + 'A', Variable[i]);
        	}
        }
        if(f == 0)
        	puts("No Change");
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
