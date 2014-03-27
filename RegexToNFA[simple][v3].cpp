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
		State(int ac=0) {
			accepted = ac;
		}
		bool accepted;
		int nameLabel;
		map<char, vector<State*> > trans;
};
class DFA {
	public:
		State* Q0;
		vector<State*> Q, F;
};
class NFA {
	public:
		static char lambda;
		State* Q0;
		vector<State*> Q;
		vector<State*> F;
		vector< vector<State*> > make_deterministic(DFA &M, vector<char> alpha);
		static NFA getNFAbyString(const char str[]);
		static NFA getNFA_Star(NFA nfa);
		static NFA getNFA_OR(NFA n1, NFA n2);
		static NFA getNFA_AND(NFA n1, NFA n2);
		void print();
		void printTable();
		void buildLabel();
	private:
		vector<State*> getSetOf(vector<State*> set_of_states, char c);
		vector<State*> getClose(vector<State*> set_of_states);
};
char NFA::lambda = 0;
vector<State*> NFA::getSetOf(vector<State*> set_of_states, char c) {
	set<State*> h;
	vector<State*> ret;
	queue<State*> q;
	State* index;
	for(int i = 0; i < set_of_states.size(); i++) {
		index = set_of_states[i];
		q.push(index);
	}
	while(!q.empty()) {
		index = q.front(), q.pop();
		vector<State*> state_trans = index->trans[c];
		for(int i = 0; i < state_trans.size(); i++) {
			if(h.find(state_trans[i]) == h.end()) {
				h.insert(state_trans[i]);
				q.push(state_trans[i]);
				ret.push_back(state_trans[i]);
			}
		}
	}
	return ret;
}
/*
 * Add to S all states reachable from it
 * using only lembda transitions of N
 */
vector<State*> NFA::getClose(vector<State*> set_of_states) {
	set<State*> h;
	vector<State*> ret;
	queue<State*> q;
	State* index;
	for(int i = 0; i < set_of_states.size(); i++) {
		index = set_of_states[i];
		q.push(index), h.insert(index);
	}
	while(!q.empty()) {
		index = q.front(), q.pop();
		ret.push_back(index);
		vector<State*> state_trans = index->trans[NFA::lambda];
		for(int i = 0; i < state_trans.size(); i++) {
			if(h.find(state_trans[i]) == h.end()) {
				h.insert(state_trans[i]);
				q.push(state_trans[i]);
			}
		}
	}
	sort(ret.begin(), ret.end());
	return ret;
}
vector< vector<State*> > NFA::make_deterministic(DFA &M, vector<char> alpha) {
	vector< vector<State*> > T;
	vector<State*> stateSet;
	stateSet.push_back(Q0);
	vector<State*> init_state = getClose(stateSet);
	T.push_back(init_state);
	M.Q.push_back(new State());
	for(int i = 0; i < T.size(); i++) {
		State* state = M.Q[i];
		for(int j = 0; j < T[i].size(); j++)
			if(T[i][j]->accepted)
				state->accepted = 1;
		state->nameLabel = i;
		if(state->accepted)	M.F.push_back(state);
		for(int j = 0; j < alpha.size(); j++) {
			if(alpha[j] == NFA::lambda)
				continue;
			vector<State*> next_state = getSetOf(T[i], alpha[j]);
			next_state = getClose(next_state);
			int existIdx = -1;
			for(int k = 0; k < T.size(); k++) {
				if(T[k] == next_state) {
					existIdx = k;
					break;
				}
			}
			if(existIdx < 0) {
				T.push_back(next_state);
				M.Q.push_back(new State());
				existIdx = T.size()-1;
			}
			M.Q[i]->trans[alpha[j]].push_back(M.Q[existIdx]);
		}
	}
	M.Q0 = M.Q[0];
	return T;
}

NFA NFA::getNFAbyString(const char str[]) {
	NFA ret;
	ret.Q.push_back(new State());
	ret.Q0 = ret.Q[0];
	for(int i = 0; str[i]; i++) {
		ret.Q.push_back(new State());
		ret.Q[i]->trans[str[i]].push_back(ret.Q[i+1]);
	}
	ret.Q[ret.Q.size()-1]->accepted = 1;
	ret.F.push_back(ret.Q[ret.Q.size()-1]);
	return ret;
}

NFA NFA::getNFA_Star(NFA nfa) {
	State *s1, *s2;
	s1 = new State();
	s2 = new State(true);
	for(int i = 0; i < nfa.F.size(); i++) {
		nfa.F[i]->accepted = 0;
		nfa.F[i]->trans[NFA::lambda].push_back(s2);
		nfa.F[i]->trans[NFA::lambda].push_back(nfa.Q0);
	}
	s1->trans[NFA::lambda].push_back(nfa.Q0);
	s1->trans[NFA::lambda].push_back(s2);
	nfa.F.clear();
	nfa.F.push_back(s2);
	nfa.Q.push_back(s1);
	nfa.Q.push_back(s2);
	nfa.Q0 = s1;
	return nfa;
}

NFA NFA::getNFA_OR(NFA n1, NFA n2) {
	State *s1, *s2;
	s1 = new State();
	s2 = new State(true);
	s1->trans[NFA::lambda].push_back(n1.Q0);
	s1->trans[NFA::lambda].push_back(n2.Q0);
	for(int i = 0; i < n1.F.size(); i++) {
		n1.F[i]->accepted = 0;
		n1.F[i]->trans[NFA::lambda].push_back(s2);
	}
	n1.F.clear();
	for(int i = 0; i < n2.F.size(); i++) {
		n2.F[i]->accepted = 0;
		n2.F[i]->trans[NFA::lambda].push_back(s2);
	}
	for(int i = 0; i < n2.Q.size(); i++)
		n1.Q.push_back(n2.Q[i]);
	n1.F.push_back(s2);
	n1.Q.push_back(s1);
	n1.Q.push_back(s2);
	n1.Q0 = s1;
	return n1;
}
NFA NFA::getNFA_AND(NFA n1, NFA n2) {
	for(int i = 0; i < n1.F.size(); i++) {
		n1.F[i]->accepted = 0;
		n1.F[i]->trans[NFA::lambda].push_back(n2.Q0);
	}
	n1.F.clear();
	for(int i = 0; i < n2.F.size(); i++)
		n1.F.push_back(n2.F[i]);
	for(int i = 0; i < n2.Q.size(); i++)
		n1.Q.push_back(n2.Q[i]);
	return n1;
}
bool cmp(const State* a, const State* b) {
	return a->nameLabel < b->nameLabel;
}
void NFA::print() {
	printf("start[%d]\n", Q0->nameLabel);
	for(int i = 0; i < F.size(); i++) {
		printf("F[%d]", F[i]->nameLabel);
	}
	puts("");
	sort(Q.begin(), Q.end(), cmp);
	for(int i = 0; i < Q.size(); i++) {
		printf("Q[%d] : ", Q[i]->nameLabel);
		for(map<char, vector<State*> >::iterator it = Q[i]->trans.begin(); 
			it != Q[i]->trans.end(); it++) {
			printf("[%c,", it->first == 0 ? '~' : it->first);
			for(vector<State*>::iterator jt = it->second.begin();
				jt != it->second.end(); jt++) {
				printf(" %d", (*jt)->nameLabel);
			}
			printf("]");
		}
		puts("");
	}
}
void NFA::printTable() {
	set<char> alpha;
	sort(Q.begin(), Q.end(), cmp);
	for(int i = 0; i < Q.size(); i++) {
		for(map<char, vector<State*> >::iterator it = Q[i]->trans.begin(); 
			it != Q[i]->trans.end(); it++) {
			alpha.insert(it->first);
		}
	}
	for(set<char>::iterator it = alpha.begin(); it != alpha.end(); it++) {
		putchar(it == alpha.begin() ? '(' : ',');
		if(*it == NFA::lambda)	printf("l");
		else					printf("%c", *it);
	}
	puts(")");
	for(int i = 0; i < Q.size(); i++) {
		for(set<char>::iterator it = alpha.begin();
			it != alpha.end(); it++) {
			vector<State*> &v = Q[i]->trans[*it];
			if(v.size() == 0)
				printf(Q[i]->accepted ? "(*)" : "(0)");
			else {
				printf("(%s", Q[i]->accepted ? "*" : "");
				sort(v.begin(), v.end(), cmp);
				for(int j = 0; j < v.size(); j++) {
					printf("%d%c", v[j]->nameLabel+1, j == v.size()-1 ? ')' : ',');
				}
			}
		} 
		puts("");
	}
}

void NFA::buildLabel() {
	set<State*> R;
	queue<State*> Q;
	int labelIdx = 0;
	Q.push(Q0), R.insert(Q0);
	while(!Q.empty()) {
		State* node = Q.front();
		Q.pop();
		node->nameLabel = labelIdx++;
		for(map<char, vector<State*> >::iterator it = node->trans.begin();
			it != node->trans.end(); it++) {
			for(vector<State*>::iterator jt = it->second.begin();
				jt != it->second.end(); jt++) {
				if(R.find(*jt) == R.end()) {
					R.insert(*jt);
					Q.push(*jt);
				}
			}
		}
	}
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
            stk.push(NFA::getNFA_Star(a));
    	} else if(token[0] == '|' || token[0] == '+') {
    		NFA a, b;
            b = stk.top(), stk.pop();
            a = stk.top(), stk.pop();
            switch(token[0]) {
            	case '|':stk.push(NFA::getNFA_OR(a, b));break;
            	case '+':stk.push(NFA::getNFA_AND(a, b));break;
        	}
    	} else {
    		stk.push(NFA::getNFAbyString(token.c_str()));
    	}
    }
    return stk.top();
}
int main() {
	char s[1024], postfix[1024];
	while(scanf("%s", s) == 1) {
		trans(s, postfix);
		// puts(postfix);
		NFA ret = calcPostfix(postfix);
		ret.buildLabel();
		ret.printTable();
	}
	return 0;
}
/*
// strings ending with a
(a|b)*a
// strings ending with bb
(a|b)*bb
// strings ending with b and not containing aa
(b)*(ab(b)*)*b

(aaaa|b)*

a*((ba)*baa)*b* 

an(ba)*bn

(b|bba)*a

*/
