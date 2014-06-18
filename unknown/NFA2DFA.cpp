#include <stdio.h> 
#include <stdlib.h>
#include <vector>
#include <map>
#include <set>
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
		vector<State*> Q, F;
		vector< vector<State*> > make_deterministic(DFA &M, vector<char> alpha);
	private:
		vector<State*> getSetOf(vector<State*> set_of_states, char c);
		vector<State*> getClose(vector<State*> set_of_states);
};
char NFA::lambda = 0;
/*
 * @return delta(S, c)
 */
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
				ret.push_back(state_trans[i]);
			}
		}
	}
	return ret;
}
/*
 * Add to S all states reachable from it
 * using only lembda transitions of N
 * @return S union delta(S, lambda)
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
/*
 * @return NFA to DFA
 */
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


vector<char> parsingAlphabetSet(char s[]) {
#define isValidAlpha(x)	((x) != ',' && (x) != '(' && (x) != ')' && !((x) >= '0' && (x) <= '9'))
	for(int i = 0; s[i]; i++) {
		if(!isValidAlpha(s[i]))
			s[i] = ' ';
	}
	vector<char> ret;
	stringstream sin(s);
	string token;
	while(sin >> token) {
		if(token == "l")
			ret.push_back(NFA::lambda);
		else
			ret.push_back(token[0]);
	}
	return ret;
}
int parsingStateTrans(char s[], int column, vector< vector< vector<int> > > &table) {
	for(int i = 0; s[i]; i++) {
		if(s[i] == '(' || s[i] == ')')
			s[i] = ' ';
	}
	stringstream sin(s);
	int ac = 0;
	vector< vector<int> > R;
	for(int i = 0; i < column; i++) {
		string token, state_index;
		sin >> token;
		for(int j = 0; j < token.length(); j++)
			if(token[j] == ',')
				token[j] = ' ';
		stringstream sin2(token);
		vector<int> S;
		while(sin2 >> state_index) {
			if(state_index == "*") {
				ac = 1;
			} else {
				int numeric_idx;
				numeric_idx = atoi(state_index.c_str());
				if(numeric_idx > 0) { // ignore zero.
					S.push_back(numeric_idx-1);
				}
			}
		}
		R.push_back(S);
	}
	table.push_back(R);
	return ac;
}
bool cmp(const State* a, const State* b) {
	return a->nameLabel < b->nameLabel;
}
void printfState(int accepted, vector<State*> mask) {
	printf("(");
	if(accepted)
		printf("*");
	sort(mask.begin(), mask.end(), cmp);
	for(int j = 0; j < mask.size(); j++) {
		printf("%d", mask[j]->nameLabel + 1);
		printf("%c", j == mask.size()-1 ? ')' : ',');
	}
	if(mask.size() == 0)
		printf("0)");
}
int main() {
	//freopen("NFA.txt", "r+t", stdin);
	//freopen("DFA.txt", "w+t", stdout);
	
	NFA nfa;
	DFA dfa;
	char s[1024];
	int state_count = 0;
	vector< vector< vector<int> > > table;
	vector<int> hasStar; // integer state label
	vector<char> alpha;
	// read alpha set 
	gets(s);
	alpha = parsingAlphabetSet(s);
	
	// read table
	while(gets(s)) {
		int ac = parsingStateTrans(s, alpha.size(), table);
		hasStar.push_back(ac);
		state_count++;	
	}
	// build basic NFA states
	for(int i = 0; i < state_count; i++) {
		nfa.Q.push_back(new State(hasStar[i]));
		nfa.Q[i]->nameLabel = i;
		if(hasStar[i])	nfa.F.push_back(nfa.Q[i]);
	}
	// init start state
	nfa.Q0 = nfa.Q[0];
	// build translate table.
	int i = 0;
	for(vector< vector< vector<int> > >::iterator it = table.begin();
		it != table.end(); it++, i++) {
		int j = 0;
		for(vector< vector<int> >::iterator jt = it->begin();
			jt != it->end(); jt++, j++) {
			for(vector<int>::iterator kt = jt->begin();
				kt != jt->end(); kt++) {
				nfa.Q[i]->trans[alpha[j]].push_back(nfa.Q[*kt]);
			}
		}
	}
	// start process NFA to DFA
	vector< vector<State*> > mask = nfa.make_deterministic(dfa, alpha);
	
	// output result
	for(map<char, vector<State*> >::iterator it = dfa.Q[0]->trans.begin(); 
			it != dfa.Q[0]->trans.end(); it++) {
		printf("%c%c", it == dfa.Q[0]->trans.begin() ? '(' : ',', it->first);
	}
	puts(")");
	for(int i = 0; i < dfa.Q.size(); i++) {
		if(mask[dfa.Q[i]->nameLabel].size() == 0)
			continue;
		printfState(dfa.Q[i]->accepted, mask[dfa.Q[i]->nameLabel]);
		for(map<char, vector<State*> >::iterator it = dfa.Q[i]->trans.begin(); 
			it != dfa.Q[i]->trans.end(); it++) {
			State *ptr = it->second[0];
			printfState(ptr->accepted, mask[ptr->nameLabel]);
		}
		puts("");
	}
	return 0;
}
/*
		void print() {
			printf("start[%p]\n", Q0);
			for(int i = 0; i < Q.size(); i++) {
				printf("Q[%p][%d] : ", Q[i], Q[i]->nameLabel);
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
		}*/
/*
(l,a,b,2)
(2,0)(3,0)(0,0)
(0,0)(4,5)(0,0)
(0,0)(0,0)(4,0)
(0,0)(5,0)(5,0)
(*,*)(*,*)(*,*)


(l,a,b,2)
(3,0)(4,0)(0,0)
(0,0)(3,1)(2,0)
(2,0)(0,0)(4,0)
(3,*)(4,*)(*,*)

(l,a,b,2) 
(2,4,6)(0)(0)
(0)(3)(0)
(6)(0)(0)
(0)(0)(5)
(6)(0)(0)
(1)(7)(0)
(*)(*)(*)

(l,a,b,2)
(0)(1,2)(1)
(0)(0)(3)
(*)(0,0)(0,0)

(l,a,b,2)
(*,0)(2)(0)
(0)(0)(3)
(0)(1,4,5)(0)
(0)(5)(0)
(0)(1)(0)
*/
