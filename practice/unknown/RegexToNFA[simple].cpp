#include <stdio.h> 
#include <stdlib.h>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
class State {
	public:
		void setAccepted(bool b) {
			accepted = b;
		}
		bool isAccepted() {
			return accepted;
		}
		State(bool ac=false) {
			accepted = ac;
		}
	private:
		bool accepted;
};
class NFA {
	public:
		static char lambda;
		int start_state;
		vector<char> alphabet;
		vector<State> states;
		vector< map<char, vector<int> > > trans_func;
		void setAlphabetSet(vector<char> s) {
			alphabet = s;
		}
		void setStateSet(vector<State> s) {
			states = s;
		}
		void setStartState(int index) {
			start_state = index;
		}
		void setTransFunc(int state_idx, map<char, vector<int> > state_trans) {
			while(trans_func.size() <= state_idx)
				trans_func.push_back(map<char, vector<int> >());
			trans_func[state_idx] = state_trans;
		}
		void print() {
			printf("(%d)\n", start_state + 1);
			printf("(");
			sort(alphabet.begin(), alphabet.end());
			for(int i = 0; i < alphabet.size(); i++) {
				if(alphabet[i] == this->lambda)
					putchar('l');
				else
					putchar(alphabet[i]);
				printf(i == alphabet.size() -1 ? ")\n" : ", ");
			}
			for(int i = 0; i < states.size(); i++) {
				for(vector<char>::iterator kt = alphabet.begin();
					kt != alphabet.end(); kt++) {
					set<int> to;
					vector<int> &toWhere = trans_func[i][*kt];
					for(int j = 0; j < toWhere.size(); j++)
						to.insert(toWhere[j]);
					for(set<int>::iterator it = to.begin();
						it != to.end(); it++) {
						putchar(it == to.begin() ? '(' : ',');
						printf("%d", *it + 1);
					}
					if(to.size() == 0 && !states[i].isAccepted())	
						printf("(0");
					else if(states[i].isAccepted()) {
						printf("%s*", to.size() > 0 ? "," : "(");
					}
					printf(")");
				}
				puts("");
			}
		}
};
char NFA::lambda = 0;
NFA getNFAbyString(const char str[]) {
	NFA ret;
	ret.setStartState(0);
	vector<State> states; 
	vector<char> alphabets;
	int len = strlen(str);
	set<char> S;
	for(int i = 0; i < len; i++) {
		map<char, vector<int> > trans_func;
		trans_func[str[i]].push_back(i+1);
		states.push_back(State());
		ret.setTransFunc(i, trans_func);
		if(S.find(str[i]) == S.end())
			S.insert(str[i]), alphabets.push_back(str[i]);
	}
	ret.setTransFunc(len, map<char, vector<int> >());
	states.push_back(State(true));
	ret.setStateSet(states);
	ret.setAlphabetSet(alphabets);
	return ret;
}
NFA getNFA_Star(NFA nfa) {
	int head = nfa.states.size();
	int tail = head + 1;
	int start = nfa.start_state;
	nfa.setTransFunc(head, map<char, vector<int> >());
	nfa.setTransFunc(tail, map<char, vector<int> >());
	for(int i = 0; i < nfa.states.size(); i++) {
		if(nfa.states[i].isAccepted()) {
			nfa.trans_func[i][NFA::lambda].push_back(start);
			nfa.trans_func[i][NFA::lambda].push_back(tail);
		}
	}
	nfa.states[nfa.states.size()-1].setAccepted(false);
	nfa.trans_func[head][NFA::lambda].push_back(start);
	nfa.setStartState(head);
	nfa.states.push_back(State(false));
	nfa.states.push_back(State(true));
	return nfa;
}
NFA getNFA_OR(NFA n1, NFA n2) {
	int head = n1.states.size() + n2.states.size();
	int tail = head + 1;
	int offset = n1.states.size();
	vector<State> states;
	map<char, vector<int> > h_trans, t_trans;
	NFA ret;
	ret.setStartState(head);
	ret.alphabet = n1.alphabet;
	for(int i = 0; i < n1.states.size(); i++) {
		ret.setTransFunc(i, n1.trans_func[i]);
		states.push_back(State(false));
		if(n1.states[i].isAccepted())
			ret.trans_func[i][NFA::lambda].push_back(tail);
	}
	for(int i = 0; i < n2.states.size(); i++) {
		ret.setTransFunc(i + offset, n2.trans_func[i]);
		for(map<char, vector<int> >::iterator it = ret.trans_func[i+offset].begin();
			it != ret.trans_func[i+offset].end(); it++) {
			if(find(ret.alphabet.begin(), ret.alphabet.end(), it->first) == ret.alphabet.end())
				ret.alphabet.push_back(it->first);
			for(vector<int>::iterator jt = it->second.begin();
				jt != it->second.end(); jt++) {
				*jt = *jt + offset;
			}
		}
		states.push_back(State(false));
		if(n2.states[i].isAccepted())
			ret.trans_func[i + offset][NFA::lambda].push_back(tail);
	}
	if(find(ret.alphabet.begin(), ret.alphabet.end(), NFA::lambda) == ret.alphabet.end())
		ret.alphabet.push_back(NFA::lambda);
	h_trans[NFA::lambda].push_back(n1.start_state);
	h_trans[NFA::lambda].push_back(n2.start_state + offset);
	ret.setTransFunc(head, h_trans);
	ret.setTransFunc(tail, t_trans);
	states.push_back(State(false));
	states.push_back(State(true));
	ret.setStateSet(states);
	return ret;
}
NFA getNFA_AND(NFA n1, NFA n2) {
	int offset = n1.states.size();
	vector<State> states;
	NFA ret = n1;
	for(int i = 0; i < n1.states.size(); i++) {
		states.push_back(State(false));
		if(n1.states[i].isAccepted())
			ret.trans_func[i][NFA::lambda].push_back(n2.start_state + offset);
	}
	for(int i = 0; i < n2.states.size(); i++) {
		ret.setTransFunc(i + offset, n2.trans_func[i]);
		for(map<char, vector<int> >::iterator it = ret.trans_func[i+offset].begin();
			it != ret.trans_func[i+offset].end(); it++) {	
			if(find(ret.alphabet.begin(), ret.alphabet.end(), it->first) == ret.alphabet.end())
				ret.alphabet.push_back(it->first);
			for(vector<int>::iterator jt = it->second.begin();
				jt != it->second.end(); jt++) {
				*jt = *jt + offset;
			}
		}
		if(n2.states[i].isAccepted())
			states.push_back(State(true));
		else
			states.push_back(State(false));
	}
	if(find(ret.alphabet.begin(), ret.alphabet.end(), NFA::lambda) == ret.alphabet.end())
		ret.alphabet.push_back(NFA::lambda);
	ret.setStateSet(states);
	return ret;
}
int priority_op(char c) {
    switch(c) {
        case '(':return 0;
        case '*':return 1;
        case '|':case '+':return 2;
    }
    return -1;
}
void trans(char infix[], char buffer[]) {
    int len = strlen(infix);
    char *ptr = buffer;
    stack<char> op;
    stack<int> elem;
    elem.push(0);
    *ptr = '\0';
    for(int i = 0; i < len; i++) {
        if(infix[i] >= 'a' && infix[i] <= 'z') {
        	while(!op.empty() && op.top() == '*') {
        		sprintf(ptr, "* ", op.top()), op.pop();
        		while(*ptr)	ptr++;
        	}
        	while(infix[i] >= 'a' && infix[i] <= 'z' && i < len) {
        		sprintf(ptr, "%c", infix[i]);
            	while(*ptr)    ptr++;
            	i++;
            }
            i--;
            sprintf(ptr, " ");
            while(*ptr)    ptr++;
            elem.top()++;
        }else {
            if(infix[i] == ')') {
                while(!op.empty() && op.top() != '(') {
                	if(op.top() == '|')	elem.top()--;
                    sprintf(ptr, "%c ", op.top()), op.pop();
                    while(*ptr) ptr++;
                }
                while(elem.top() > 1) {
                    sprintf(ptr, "+ ");
                    while(*ptr) ptr++;
                    elem.top()--;
                }
                elem.pop();
                elem.top()++;
                op.pop();
            } else {
                if(infix[i] != '(') {
                	while(!op.empty() && priority_op(op.top()) >= priority_op(infix[i])) {
                    	sprintf(ptr, "%c ", op.top()), op.pop();
                    	while(*ptr) ptr++;
                	}
                } else {
                	while(!op.empty() && op.top() == '*') {
                		sprintf(ptr, "* ", op.top()), op.pop();
                		while(*ptr)	ptr++;
                	}
                	elem.push(0);
                }
                op.push(infix[i]);
            }
        }
    }
    while(!op.empty()) {
        sprintf(ptr, "%c ", op.top()), op.pop();
        while(*ptr) ptr++;
    }
    while(elem.top() > 1) {
        sprintf(ptr, "+ ");
        while(*ptr) ptr++;
        elem.top()--;
    }
    elem.pop();
}
NFA calcPostfix(char postfix[]) {
    int len = strlen(postfix);
    stack<NFA> stk;
    stringstream sin(postfix);
    string token;
    while(sin >> token) {
    	if(token[0] == '*') {
    		NFA a;
            a = stk.top(), stk.pop();
            stk.push(getNFA_Star(a));
    	} else if(token[0] == '|' || token[0] == '+') {
    		NFA a, b;
            b = stk.top(), stk.pop();
            a = stk.top(), stk.pop();
            switch(token[0]) {
            	case '|':stk.push(getNFA_OR(a, b));break;
            	case '+':stk.push(getNFA_AND(a, b));break;
        	}
    	} else {
    		stk.push(getNFAbyString(token.c_str()));
    	}
    }
    return stk.top();
}
int main() {/*
	NFA test1 = getNFAbyString("a");
	NFA test2 = getNFAbyString("baa");
	NFA test3 = getNFA_AND(test1, test2);
	test3.print();*/
	char s[1024], postfix[1024];
	while(scanf("%s", s) == 1) {
		trans(s, postfix);
		puts(postfix);
		NFA ret = calcPostfix(postfix);
		ret.print();
	} 
	return 0;
}
/*
[a-z] | * ()
// strings ending with a
(a|b)*a
// strings ending with bb
(a|b)*bb
// strings ending with b and not containing aa
(b)*(ab(b)*)*b

(aaaa|b)*

a*((ba)*baa)*b* 

an(ba)*bn

*/
