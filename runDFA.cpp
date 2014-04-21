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
		int runDFA(const char s[]);
};
int DFA::runDFA(const char s[]) {
	State *p;
	p = Q0;
	for(int i = 0; s[i]; i++) {
		if(p->trans.find(s[i]) == p->trans.end())
			return 0;
		p = p->trans[s[i]][0];
	}
	return p->accepted;
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
	while(sin >> token)
		ret.push_back(token[0]);
	return ret;
}
int parsingStateTrans(char s[], int column, vector< vector< string > > &table) {
	for(int i = 0; s[i]; i++) {
		if(s[i] == '(' || s[i] == ')')
			s[i] = ' ';
	}
	stringstream sin(s);
	vector< string > R;
	for(int i = 0; i < column + 1; i++) {
		string token;
		sin >> token;
		R.push_back(token);
	}
	table.push_back(R);
	int ac = 0;
	for(int i = 0; i < R[0].length(); i++)
		if(R[0][i] == '*')
			ac = 1;
	return ac;
}
int main() {
	freopen("DFAjudge.txt", "r+t", stdin);
	freopen("DFAresult.txt", "w+t", stdout);
	DFA dfa;
	char s[1024];
	gets(s);
	vector<char> alpha = parsingAlphabetSet(s);
	
	int state_count = 0;
	vector< vector< string > > table;
	vector<int> hasStar;
	while(gets(s)) {
		if(s[0] != '(')	break;
		int ac = parsingStateTrans(s, alpha.size(), table);
		hasStar.push_back(ac);
		state_count++;	
	}
	for(int i = 0; i < state_count; i++) {
		dfa.Q.push_back(new State(hasStar[i]));
		dfa.Q[i]->nameLabel = i;
		if(hasStar[i])	dfa.F.push_back(dfa.Q[i]);
	}
	dfa.Q0 = dfa.Q[0];
	int i = 0;
	for(vector< vector< string > >::iterator it = table.begin();
		it != table.end(); it++, i++) {
		string start = table[i][0];
		for(int j = 1; j <= alpha.size(); j++) {
			string end = table[i][j];
			for(int k = 0; k < table.size(); k++) {
				if(table[k][0] == end)
					dfa.Q[i]->trans[alpha[j-1]].push_back(dfa.Q[k]);
			}
		}
	}
	puts(dfa.runDFA(s) ? "valid" : "error");
	return 0;
}
/*
Sample Input: 
(a,b)
(1,2)(*3,4,5)(0)
(*3,4,5)(*5)(*4,5)
(*5)(0)(0)
(*4,5)(*5)(*5)
abbbb

(a,b)
(1,2)(*3,4,5)(0)
(*3,4,5)(*5)(*4,5)
(*5)(0)(0)
(*4,5)(*5)(*5)
ab

(a,b)
(1,2,3)(*1,2,3,4)(*2,3,4)
(*1,2,3,4)(*1,2,3,4)(*2,3,4)
(*2,3,4)(*1,2,3,4)(*2,3,4)
a
------------------
Sample Output:
error
valid
valid
*/
