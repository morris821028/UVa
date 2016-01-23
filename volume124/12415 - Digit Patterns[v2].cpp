#include <bits/stdc++.h>
using namespace std;

const int MAXSTATE = 32767;
const int epsilon = 0;

int toIndex(char c) {
	return c - '0' + 1;
}
struct State {
	vector<State*> trans[11];
	int ac, label;
	State() {
		ac = label = 0;
		for (int i = 0; i < 11; i++)
			trans[i].clear();
	}
} _mem[MAXSTATE];
int nodesize = 0;
State *newState() {
	assert(nodesize < MAXSTATE);
	State *p = &_mem[nodesize++];
	*p = State();
	return p;
}

struct NFA {
	State *st, *ac;
	NFA() {
		st = ac = NULL;
	}
	NFA(char c) {
		st = newState(), ac = newState();
		ac->ac = 1;
		st->trans[toIndex(c)].push_back(ac);
	}
	NFA(NFA L, char c) {	// (A)*
		st = ac = NULL;
		if (c != '*')
			return ;
		st = newState(), ac = newState();
		ac->ac = 1;
		st->trans[epsilon].push_back(L.st);
		L.st->trans[epsilon].push_back(L.ac);
		L.ac->trans[epsilon].push_back(L.st);
		L.ac->trans[epsilon].push_back(ac);
		L.ac->ac = 0;
	}
	NFA(NFA L, NFA R, char c) {
		if (R.st == NULL) {
			st = L.st, ac = L.ac;
			return;
		}
		if (c == '|') {
			st = newState(), ac = newState();
			ac->ac = 1;
			st->trans[epsilon].push_back(L.st);
			st->trans[epsilon].push_back(R.st);
			L.ac->trans[epsilon].push_back(ac);
			R.ac->trans[epsilon].push_back(ac);
			L.ac->ac = R.ac->ac = 0;
		} else if (c == '&') {
			st = newState(), ac = newState();
			ac->ac = 1;
			st->trans[epsilon].push_back(L.st);
			L.ac->trans[epsilon].push_back(R.st);
			R.ac->trans[epsilon].push_back(ac);
			L.ac->ac = R.ac->ac = 0;
		}
	}
};

NFA parser(string exp) {
	if (exp.length() == 0)
		return NFA();
	if (exp.length() == 1)
		return NFA(exp[0]);
		
	int l = 0, pos = -1;
	for (int i = 0; i < exp.length(); i++) {
		if (exp[i] == '(') {
			l++;
		} else if (exp[i] == ')') {
			l--;
		} else if (exp[i] == '+') {
			if (l == 0) {
				pos = i;
				break;
			}
		}
	}
	
	if (pos != -1) {
		NFA L = parser(exp.substr(0, pos));
		NFA R = parser(exp.substr(pos+1));
		return NFA(L, R, '|');
	}
	
	int hasStar = 0;
	string ls, rs;
	
	if (exp[0] == '(') {
		for (int i = 0; i < exp.length(); i++) {
			if (exp[i] == '(') {
				l++;
			} else if (exp[i] == ')') {
				l--;
				if (l == 0) {	// (...)...
					if (i+1 < exp.length() && exp[i+1] == '*') {	// (...)*...
						hasStar = 1;
						ls = exp.substr(1, i-1), rs = exp.substr(i+2);
					} else {	// (...)...
						ls = exp.substr(1, i-1), rs = exp.substr(i+1);
					}
					break;
				}
			}
		}
	} else {	// ...(...) or ...*... or ......
		for (int i = 0; i < exp.length(); i++) {
			if (exp[i] == '(') {
				l++;
			} else if (exp[i] == ')') {
				l--;
			}
			if (l == 0) {
				if (i+1 < exp.length() && exp[i+1] == '*') {
					hasStar = 1;
					ls = exp.substr(0, i+1), rs = exp.substr(i+2);
				} else {
					ls = exp.substr(0, i+1), rs = exp.substr(i+1);
				}
				break;
			}
		}
	}
	for (int i = 0; rs.length() > 0; ) {
		while (i < rs.length() && rs[i] == '*')
			i++;
		rs = rs.substr(i);
		break;
	}
	NFA L = parser(ls);
	NFA R = parser(rs);
	if (hasStar)
		L = NFA(L, '*');
	return NFA(L, R, '&');
}

State *gmap[MAXSTATE];
int relabel(NFA A) {
    int size = 0;
    State *u, *v;
    queue<State*> Q;
    Q.push(A.st), A.st->label = ++size;
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        gmap[u->label] = u;
        for (int it = 0; it < 11; it++) {
        	for (int i = 0; i < u->trans[it].size(); i++) {
        		v = u->trans[it][i];
                if (v->label == 0) {
                    v->label = ++size;
                    Q.push(v);
                }
			}
		}
    }
    return size;
}

char s[16777216];
int used[MAXSTATE], ACable[MAXSTATE];

int closure(vector<int> &A, int x, int cases) {
	queue<int> Q;
	State *u;
	int accept = 0;
	if (used[x] != cases)
		A.push_back(x), used[x] = cases;
	Q.push(x);
	while (!Q.empty()) {
		x = Q.front(), Q.pop();
		u = gmap[x];
		accept |= u->ac;
		if (u->trans[epsilon].size() == 0)
			continue;
		for (auto &y : u->trans[epsilon]) {
			if (used[y->label] != cases) {
				Q.push(y->label), used[y->label] = cases;
				A.push_back(y->label);
			}
		}
	}
	return accept;
}
void rebuild(int n, int ctype) {
	memset(ACable, 0, sizeof(ACable));
	memset(used, 0, sizeof(used));
	int cases = 0;
	for (int i = 1; i <= n; i++) {
		cases++;
		vector<int> cc;
		closure(cc, i, cases);
		for (int j = 1; j <= ctype; j++) {
			set<int> S;
			for (int k = 0; k < cc.size(); k++) {
				State *u = gmap[cc[k]];
				for (auto &p : u->trans[j])
					S.insert(p->label);
				ACable[i] |= u->ac;
			}
			State *u = gmap[i];
			u->trans[j].clear();
			for (auto &x : S)
				u->trans[j].push_back(gmap[x]);
		}
	}
}
int main() {
	int n, m;
	char regex[512];
	while (scanf("%d %s", &n, regex) == 2) {
		nodesize = 0;	// global
		NFA nfa = parser(regex);
		m = relabel(nfa);
		rebuild(m, n);
		scanf("%s", s);
		
		memset(used, 0, sizeof(used));
		int cases = 0, flag = 0;
		
		vector<int> A;
		cases++;
		A.push_back(1);
		for (int i = 0; s[i]; i++) {
			vector<int> next;
			cases++;
			int accept = 0;
			for (int j = 0; j < A.size(); j++) {
				int x = A[j];
				State *u = gmap[x];
				if (u->trans[toIndex(s[i])].size() == 0)
					continue;
				for (auto &y : u->trans[toIndex(s[i])]) {
					if (used[y->label] != cases) {
						used[y->label] = cases, next.push_back(y->label);
						accept |= ACable[y->label];
					}
				}
			}
			if (used[1] != cases)
				used[1] = cases, next.push_back(1);
			A = next;
			if (accept) {
				if (flag)	putchar(' ');
				flag = 1;
				printf("%d", i+1);
			}
		}
		puts("");
	}
	return 0;
}
/*
6 1(2+3)*4
012345
2 00*(10+100)*
00100
*/
