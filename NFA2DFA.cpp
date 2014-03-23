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
		void setAccepted(bool b) {
			accepted = b;
		}
		bool isAccepted() {
			return accepted;
		}
		State() {
			accepted = 0;
		}
	private:
		bool accepted;
};
class DFA {
	public:
		int start_state;
		vector<char> alphabet;
		vector<State> states;
		vector< map<char, int> > trans_func;
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
			printf("Start state : %d\n", start_state);
			printf("Accept states : {");
			for(int i = 0, j = 0; i < states.size(); i++) {
				if(states[i].isAccepted()) {
					if(j)	putchar(',');
					printf("%d", i), j = 1;
				}
			}
			puts("}");
			printf("Alphabet set : {");
			for(int i = 0; i < alphabet.size(); i++) {
				if(alphabet[i] == this->lambda)
					putchar('~');
				else
					putchar(alphabet[i]);
				printf(i == alphabet.size() -1 ? "}\n" : ", ");
			}
			puts("Transition Table :");
			puts("---------+---------------------");
			puts("State[x] | (alpha, State[y])");
			puts("---------+---------------------");
			for(int i = 0; i < states.size(); i++) {
				printf("State[%d] | ", i, states[i].isAccepted());
				for(map<char, vector<int> >::iterator jt = trans_func[i].begin();
					jt != trans_func[i].end(); jt++) {
					char alpha = jt->first;
					if(alpha == this->lambda)
						alpha = '~';
					for(int j = 0; j < jt->second.size(); j++) {
						printf("(%c, %d)", alpha, jt->second[j]);
					}
				}
				puts("");
			}
			puts("---------+---------------------");
		}
};
char NFA::lambda = 0;
/*
 * Add to S all states reachable from it
 * using only 'c' transitions of N
 */
vector<int> getSetOf(vector<int> set_of_states, NFA &N, char c) {
	set<int> h;
	vector<int> ret;
	queue<int> q;
	int index;
	for(int i = 0; i < set_of_states.size(); i++) {
		index = set_of_states[i];
		q.push(index);
	}
	while(!q.empty()) {
		index = q.front(), q.pop();
		vector<int> state_trans = N.trans_func[index][c];
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
vector<int> getClose(vector<int> set_of_states, NFA &N) {
	set<int> h;
	vector<int> ret;
	queue<int> q;
	int index;
	for(int i = 0; i < set_of_states.size(); i++) {
		index = set_of_states[i];
		q.push(index), h.insert(index);
	}
	while(!q.empty()) {
		index = q.front(), q.pop();
		ret.push_back(index);
		vector<int> state_trans = N.trans_func[index][NFA::lambda];
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

vector< vector<int> > make_deterministic(NFA N, DFA &M) {
	vector< vector<int> > T;
	vector<int> next_state;
	next_state.push_back(N.start_state);
	vector<int> init_state = getClose(next_state, N);
	T.push_back(init_state);
	M.start_state = 0;
	for(int i = 0; i < N.alphabet.size(); i++) {
		if(N.alphabet[i] != NFA::lambda) {
			M.alphabet.push_back(N.alphabet[i]);
		}
	}
	for(int i = 0; i < T.size(); i++) {
		State state;
		map<char, int> state_trans;
		for(int j = 0; j < T[i].size(); j++)
			if(N.states[T[i][j]].isAccepted())
				state.setAccepted(true);
		M.states.push_back(state);
		for(int j = 0; j < M.alphabet.size(); j++) {
			vector<int> next_state = getSetOf(T[i], N, M.alphabet[j]);
			next_state = getClose(next_state, N);
			int existIdx = -1;
			for(int k = 0; k < T.size(); k++) {
				if(T[k] == next_state) {
					existIdx = k;
					break;
				}
			}
			if(existIdx < 0) {
				T.push_back(next_state);
				existIdx = T.size()-1;
			}
			state_trans[M.alphabet[j]] = existIdx;
		}
		M.trans_func.push_back(state_trans);
	}
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
void parsingStateTrans(char s[], map<char, vector<int> >& state_trans, State &state, NFA &nfa) {
	for(int i = 0; s[i]; i++) {
		if(s[i] == '(' || s[i] == ')')
			s[i] = ' ';
	}
	stringstream sin(s);
	for(int i = 0; i < nfa.alphabet.size(); i++) {
		string token, state_index;
		sin >> token;
		for(int j = 0; j < token.length(); j++)
			if(token[j] == ',')
				token[j] = ' ';
		stringstream sin2(token);
		while(sin2 >> state_index) {
			if(state_index == "*") {
				state.setAccepted(true);
			} else {
				int numeric_idx;
				numeric_idx = atoi(state_index.c_str());
				if(numeric_idx > 0) { // ignore zero.
					state_trans[nfa.alphabet[i]].push_back(numeric_idx - 1);
				}
			}
		}
	}
}
void printfState(int accepted, vector<int> mask) {
	printf("(");
	if(accepted)
		printf("*");
	for(int j = 0; j < mask.size(); j++) {
		printf("%d", mask[j] + 1);
		printf("%c", j == mask.size()-1 ? ')' : ',');
	}
	if(mask.size() == 0)
		printf("0)");
}
int main() {
	NFA nfa;
	DFA dfa;
	char s[1024];
	gets(s);
	nfa.setAlphabetSet(parsingAlphabetSet(s));
	
	int state_count = 0;
	vector<State> states;
	while(gets(s)) {
		State state;
		map<char, vector<int> > state_trans;
		parsingStateTrans(s, state_trans, state, nfa);
		nfa.setTransFunc(state_count, state_trans);
		states.push_back(state);
		state_count++;	
	}
	nfa.setStateSet(states);
	nfa.setStartState(0);
	vector< vector<int> > mask = make_deterministic(nfa, dfa);
	for(int i = 0; i < dfa.states.size(); i++) {
		if(mask[i].size() == 0)
			continue;
		printfState(dfa.states[i].isAccepted(), mask[i]);
		for(int j = 0; j < dfa.alphabet.size(); j++) {
			int sidx = dfa.trans_func[i][dfa.alphabet[j]];
			printfState(dfa.states[sidx].isAccepted(), mask[sidx]);
		}
		puts("");
	}	
	//nfa.print();
	return 0;
}
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
*/
