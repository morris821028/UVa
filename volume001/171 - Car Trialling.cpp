#include <stdio.h> 
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string.h>
#include <ctype.h>
#include <assert.h>
using namespace std;

#define HTMLProduction
// #define DEBUG

class Production {
	public:
		int 			label;
		string 			LHS;
		vector<string> 	RHS;
		
		Production(string L = "", vector<string> R = vector<string>(), int l=0) {
			LHS = L;
			RHS = R;
			label = l;
		}

		bool operator<(const Production &p) const {
			if(LHS != p.LHS)
				return LHS < p.LHS;
			for(size_t i = 0, j = 0; i < RHS.size() && j < p.RHS.size(); i++, j++) {
				if(RHS[i] != p.RHS[i])
					return RHS[i] < p.RHS[i];
			}
			return RHS.size() < p.RHS.size();
		}
		
		bool operator==(const Production &p) const {
			if(LHS != p.LHS || RHS.size() != p.RHS.size())
				return false;
			for(size_t i = 0, j = 0; i < RHS.size(); i++, j++) {
				if(RHS[i] != p.RHS[i])
					return false;
			}
			return true;
		}
		
		bool operator!=(const Production &p) const {
			return !(*this == p);
		}
		
		void print() {
			printf("%s -> ", LHS.c_str());
			for(size_t i = 0; i < RHS.size(); i++)
				printf("%s", RHS[i].c_str());
		}
};

class Grammar {
	public:
		/* LR parsing */
		class ConfigurationSet {
			public:
				class State {
					public:
						int dot;
						vector<string> lookahead;
						
						State(int d=0, vector<string> l=vector<string>()):
							dot(d), lookahead(l) {}
						bool operator<(const State &x) const {
							return dot < x.dot;
						}
						bool operator!=(const State &x) const {
							return dot != x.dot;
						}
				};
				
				set< pair<Production, State> > 	configs;
				int 							label;
				ConfigurationSet() {
					label = 0;
				}
				/* method */
				static ConfigurationSet closure0(ConfigurationSet& s, Grammar& g);
				static ConfigurationSet go_to0(ConfigurationSet& s, string X, Grammar& g);
				void print(Grammar &g) {
					set< pair<Production, State> >::iterator it;
					Production p;
					
					for(it = configs.begin(); it != configs.end(); it++) {
						p = it->first;
						printf("%s ->", p.LHS.c_str());
						for(size_t i = 0; i < p.RHS.size(); i++) {
							if(i == it->second.dot)
								printf("¡E");
							printf(" %s ", p.RHS[i].c_str());
						}
						if(it->second.dot == p.RHS.size())
							printf("¡E");
						printf(" ,{");
						set<string> fset = g.follow_set[p.LHS];
						for(set<string>::iterator jt = fset.begin();
							jt != fset.end(); jt++) {
							if(jt != fset.begin())
								cout << ", ";
							cout << *jt;
						}
						printf("}");
						puts("");
					}
				}
				bool operator<(const ConfigurationSet &x) const {
					if(configs.size() != x.configs.size())
						return configs.size() < x.configs.size();
					for(set< pair<Production, State> >::iterator it = configs.begin(), jt = x.configs.begin();
						it != configs.end(); it++, jt++) {
						if(it->first != jt->first)
							return it->first < jt->first;
						if(it->second != jt->second)
							return it->second < jt->second;
					}
					return false;
					// return label < x.label;
				}
		};		
		
		static const string 		lambda;
		set<string>					symbols;
		string 						start_symbol;
		vector<Production> 			rules;
		/* LL(1) attribute */
		map<string, set<string> > 	first_set;
		map<string, set<string> > 	follow_set;
		map<string, bool> 			derives_lambda;
		map<string, map<string, Production> >	lltable;
		/* LR attribute */
		vector<ConfigurationSet>	LRstates;
		map<int, map<string, int> >	go_to_table;
		map<int, int>				action_table;
		
		/* common method */
		static bool isNonterminal(string token);
		void buildSymbols();
		/* LL(1) method */
		map<string, bool> mark_lambda();
		void fill_first_set();
		void fill_follow_set();
		set<string> compute_first(vector<string> rhs);
		set<string> get_predict_set(Production p);
		void fill_lltable();
		void lldriver(queue<string> tokens);
		/* LR method*/
		void build_CFSM();
		void build_action();
		void lr0driver(queue<string> tokens);
		int slr1driver(queue<string> tokens);
		void lalr1driver(queue<string> tokens);
		/* homework */
		void hw_build_CFSM();
};
/* ------------------------
ConfigurationSet method
-------------------------- */
Grammar::ConfigurationSet Grammar::ConfigurationSet::closure0(ConfigurationSet& s, Grammar& g) {
	ConfigurationSet 	r = s;
	bool				changes;
	string				A;
	Production			P;
	int 				dotPos;
	
	set< pair<Production, State> >::iterator it;
	do {
		changes = false;
		for(it = r.configs.begin(); it != r.configs.end(); it++) {
			P = it->first;
			dotPos = it->second.dot;
			if(dotPos >= P.RHS.size() || P.RHS[dotPos] == Grammar::lambda)
				continue;
			A = P.RHS[dotPos];
			if(Grammar::isNonterminal(A)) {
				/* B -> x.Ay */
				/* Predict productions with A as the left-hand side */
				for(size_t i = 0; i < g.rules.size(); i++) {
					if(g.rules[i].LHS == A) {
						if(r.configs.find(make_pair(g.rules[i], State(0))) == r.configs.end()) {
							r.configs.insert(make_pair(g.rules[i], State(0)));
							changes = true;
						}
					}
				}
			}
		}
	} while(changes);
	return r;
}
Grammar::ConfigurationSet Grammar::ConfigurationSet::go_to0(ConfigurationSet& s, string X, Grammar& g) {
	ConfigurationSet sb;
	set< pair<Production, State> >::iterator it;
	Production 	P;
	int 		dotPos;
	
	for(it = s.configs.begin(); it != s.configs.end(); it++) {
		P = it->first;
		dotPos = it->second.dot;
		if(dotPos >= P.RHS.size() || P.RHS[dotPos] == Grammar::lambda)
			continue;
		if(P.RHS[dotPos] == X) {
			State state(dotPos + 1, it->second.lookahead);
			sb.configs.insert(make_pair(P, state));
		}
	}
	return closure0(sb, g);
}
/* ------------------------
Grammar method
-------------------------- */
const string Grammar::lambda("l");

set<string> Grammar::compute_first(vector<string> rhs) {
	set<string> result;
	size_t 		i;
	
	if(rhs.size() == 0 || rhs[0] == Grammar::lambda) {
		result.insert(Grammar::lambda);
	} else {
		result = first_set[rhs[0]];
		for(i = 1; i < rhs.size() && 
			first_set[rhs[i-1]].find(Grammar::lambda) != first_set[rhs[i-1]].end(); i++) {
			set<string> f = first_set[rhs[i]];
			f.erase(Grammar::lambda);
			result.insert(f.begin(), f.end());	
		}
		if(i == rhs.size() 
			&& first_set[rhs[i-1]].find(Grammar::lambda) != first_set[rhs[i-1]].end()) {
			result.insert(Grammar::lambda);
		} else {
			result.erase(Grammar::lambda);
		}
	}
	
	return result;
} 
/*
 * please call get_predict_set() after fill_follow_set() and fill_first_set()
 */
set<string> Grammar::get_predict_set(Production p) {
	set<string> result;
	set<string> rfirst;
	
	rfirst = compute_first(p.RHS);
	if(rfirst.find(Grammar::lambda) != rfirst.end()) {
		rfirst.erase(Grammar::lambda);
		result.insert(rfirst.begin(), rfirst.end());
		rfirst = follow_set[p.LHS];
		result.insert(rfirst.begin(), rfirst.end());
	} else {
		result.insert(rfirst.begin(), rfirst.end());
	}
	
	return result;
}
/*
 * 
 */
void Grammar::fill_lltable() {
	string		A; // nonterminal
	Production 	p;
	
	for(size_t i = 0; i < rules.size(); i++) {
		p = rules[i];
		A = p.LHS;
		set<string> predict_set = get_predict_set(p);
		
		for(set<string>::iterator it = predict_set.begin();
			it != predict_set.end(); it++) {
			assert(lltable[A].find(*it) == lltable[A].end());
			lltable[A][*it] = p;
		}
	}
	
}
void Grammar::buildSymbols() {
	symbols.clear();
	for(size_t i = 0; i < rules.size(); i++) {
		symbols.insert(rules[i].LHS);
		for(size_t j = 0; j < rules[i].RHS.size(); j++) {
			symbols.insert(rules[i].RHS[j]);
		}
	}
}
bool Grammar::isNonterminal(string token) {

#ifdef HTMLProduction
	if(token == Grammar::lambda)
		return false;
	if(token[0] == '<' && token[token.length() - 1] == '>')
		return true;
	return false;
#else
	if(token == Grammar::lambda)
		return false;
	for(size_t i = 0; i < token.length(); i++) {
		if(isupper(token[i]))
			return true;
	}
	return false;
#endif
}
/* ------------------------
Grammar LL method
-------------------------- */
map<string, bool> Grammar::mark_lambda() {
	bool 				rhs_derives_lambda;
	bool 				changes;
	Production 			p;
	
	derives_lambda.clear();
	
	/* initially, nothing is marked. */
	for(size_t i = 0; i < rules.size(); i++) {
		derives_lambda[rules[i].LHS] = false;
	}
	do {
		changes = false;
		for(size_t i = 0; i < rules.size(); i++) {
			p = rules[i];
			if(!derives_lambda[p.LHS]) {
				if(p.RHS.size() == 0 || p.RHS[0] == Grammar::lambda) {
					changes = derives_lambda[p.LHS] = true;
					continue;
				}
				/* does each part of RHS derive lambda ? */
				rhs_derives_lambda = derives_lambda[string(p.RHS[0])];
				for(size_t j = 1; j < p.RHS.size(); j++) {
					rhs_derives_lambda &= derives_lambda[p.RHS[j]];
				}
				if(rhs_derives_lambda) {
					changes = true;
					derives_lambda[p.LHS] = true;
				}
			}
		}
	} while(changes);
	return derives_lambda;
}
void Grammar::fill_first_set() {
	
	string 		A; // nonterminal
	string 		a; // terminal
	Production 	p;
	bool 		changes;
		
	mark_lambda();
	first_set.clear();
	
	for(size_t i = 0; i < rules.size(); i++) {
		A = rules[i].LHS;
		if(derives_lambda[A])
			first_set[A].insert(Grammar::lambda);
	}
	
	for(size_t i = 0; i < rules.size(); i++) {
		for(size_t j = 0; j < rules[i].RHS.size(); j++) {
			a = rules[i].RHS[j];
			if(!isNonterminal(a)) {
				if(a != Grammar::lambda)
					first_set[a].insert(a);
				if(j == 0) { // A -> aXX
					first_set[rules[i].LHS].insert(a);
				}
			}
		}
	}
	
	do {
		changes = false;
		for(size_t i = 0; i < rules.size(); i++) {
			p = rules[i];
			set<string> rfirst = compute_first(p.RHS);
			size_t oldsize = first_set[p.LHS].size();
			first_set[p.LHS].insert(rfirst.begin(), rfirst.end());
			size_t newsize = first_set[p.LHS].size();
			if(oldsize != newsize)
				changes = true;
		}
	} while(changes);
} 

void Grammar::fill_follow_set() {
	string 	A, B; // nonterminal
	Production 	p;
	bool 	changes;
	
	for(size_t i = 0; i < rules.size(); i++) {
		A = rules[i].LHS;
		follow_set[A].clear();
	}
	
	follow_set[start_symbol].insert(Grammar::lambda);
		
	do {
		changes = false;
		for(size_t i = 0; i < rules.size(); i++) {
			/* A -> a B b
			 * I.e. for each production and each occurrence
			 * of a nonterminal in its right-hand side. 
			 */
			p = rules[i];
			A = p.LHS;
			for(size_t j = 0; j < p.RHS.size(); j++) {
				B = p.RHS[j];
				if(isNonterminal(B)) {
					vector<string> beta(p.RHS.begin() + j + 1, p.RHS.end());
					set<string> rfirst = compute_first(beta);
					size_t oldsize = follow_set[B].size();
					
					if(rfirst.find(Grammar::lambda) == rfirst.end()) {
						follow_set[B].insert(rfirst.begin(), rfirst.end());	
					} else {
						rfirst.erase(Grammar::lambda);
						follow_set[B].insert(rfirst.begin(), rfirst.end());	
						rfirst = follow_set[A];
						follow_set[B].insert(rfirst.begin(), rfirst.end());
					}
					size_t newsize = follow_set[B].size();			
					if(oldsize != newsize)
						changes = true;
				}
			}
		}
	} while(changes);
}

void Grammar::lldriver(queue<string> tokens) {
	stack<string> 	stk;
	string 			X;
	string			a;
	Production		p;
	/* Push the Start Symbol onto an empty stack */
	stk.push(start_symbol);
	
	while(!stk.empty() && !tokens.empty()) {
		X = stk.top();
		a = tokens.front();
		// cout << X << " " << a << endl;
		if(isNonterminal(X) && lltable[X].find(a) != lltable[X].end()) {
			p = lltable[X][a];
			stk.pop();
			for(int i = p.RHS.size() - 1; i >= 0; i--) {
				if(p.RHS[i] == Grammar::lambda)
					continue;
				stk.push(p.RHS[i]);
			}
		} else if(X == a) {
			stk.pop();
			tokens.pop();
		} else if(lltable[X].find(Grammar::lambda) != lltable[X].end()) {
			stk.pop();
		} else {
			/* Process syntax error. */
			puts("Bad!");
			return;
		}
	}
	while(!stk.empty()) {
		X = stk.top();
		if(lltable[X].find(Grammar::lambda) != lltable[X].end())
			stk.pop();
		else
			break;
	}
	if(tokens.size() == 0 && stk.size() == 0)
		puts("Good");
	else
		puts("Bad!");
	return;
}
/* ------------------------
Grammar LR method
-------------------------- */
void Grammar::build_action() {
	ConfigurationSet 	s;
	Production 			P;
	int					dotPos;
	set< pair<Production, ConfigurationSet::State> >::iterator it;
	
	for(size_t i = 0; i < LRstates.size(); i++) {
		s = LRstates[i];
		int reduce = 0, rule = 0, accept = 1;
		for(it = s.configs.begin(); it != s.configs.end(); it++) {
			P = it->first, dotPos = it->second.dot;
			if(dotPos == P.RHS.size())
				reduce++, rule = P.label;
			accept &= P.LHS == Grammar::start_symbol;
		}
		if(accept == 1)
			action_table[i] = 0;
		else if(reduce == 1)
			action_table[i] = -1;
		else
			action_table[i] = 1;
	}
#ifdef DEBUG
	printf("State |");
	for(size_t i = 0; i < LRstates.size(); i++)
		printf("%5d|", i);
	puts("");
	printf("Action|");
	for(size_t i = 0; i < action_table.size(); i++) {
		printf("%5d|", action_table[i]);
	}
	puts("");
#endif
}
void Grammar::build_CFSM() {
	set<ConfigurationSet> 	S;
	queue<ConfigurationSet>	Q;
	ConfigurationSet 		s0, sb;
	int 					label = 0;
	ConfigurationSet::State state;
	
	state.dot = 0;
	state.lookahead = vector<string>();
	state.lookahead.push_back(Grammar::lambda);
	for(size_t i = 0; i < rules.size(); i++) {
		if(rules[i].LHS == this->start_symbol) {
			s0.configs.insert(make_pair(rules[i], state));
		}
	}
	s0 = ConfigurationSet::closure0(s0, *this);
	s0.label = label++;
	
	S.insert(s0);
	Q.push(s0);
	
	buildSymbols();
	/* hw need */
	map<int, vector< pair<int, string> > > hwPrint;
	/* hw need */
	while(!Q.empty()) {
		s0 = Q.front(), Q.pop();
		LRstates.push_back(s0);
		for(set<string>::iterator it = symbols.begin();
			it != symbols.end(); it++) {
			sb = ConfigurationSet::go_to0(s0, *it, *this);
			if(sb.configs.size() > 0) {
				if(S.find(sb) == S.end()) {
					sb.label = label++;
					S.insert(sb);
					Q.push(sb);
				}
				
				go_to_table[s0.label][*it] = (* S.find(sb)).label;
				/* hw need */
				hwPrint[(* S.find(sb)).label].push_back(make_pair(s0.label, *it));
			}
		}
	}
	// build_action();
#ifdef DEBUG	
	printf("Total State: %d\n", label);
	for(int i = 0; i < label; i++) {
		if(hwPrint[i].size() > 0) {
			printf("State %d from", i);
			for(vector< pair<int, string> >::iterator it = hwPrint[i].begin();
				it != hwPrint[i].end(); it++) {
				printf("%cState %d(%s)", it == hwPrint[i].begin() ? ' ' : ',', it->first, it->second.c_str());
			}
			puts("");
		} else {
			printf("State %d\n", i);
		}
		LRstates[i].print(*this);
		puts("");
	}
#endif
}
int Grammar::slr1driver(queue<string> tokens) {
	stack<int> 		stateStk;
	stack<string> 	tokenStk;
	int 			state;
	string			X;
	
	stateStk.push(0); /* push start state */
	while(!tokens.empty()) {
		state = stateStk.top();
		X = tokens.front();
#ifdef DEBUG 
		puts("");
		printf("state %d front %s\n", state, X.c_str());
		LRstates[state].print(*this);
		for (std::stack<int> dump = stateStk; !dump.empty(); dump.pop())
        	std::cout << "state stack "<< dump.top() << '\n';
		for (std::stack<string> dump = tokenStk; !dump.empty(); dump.pop())
        	std::cout << "token stack "<< dump.top() << '\n';
#endif
		int reduce = 0, shift = 0;
		Production P;
		for(set< pair<Production, ConfigurationSet::State> >::iterator it = LRstates[state].configs.begin(); 
			it != LRstates[state].configs.end(); it++) {
			Production q = it->first;
			ConfigurationSet::State s = it->second;
			if(follow_set[q.LHS].find(X) != follow_set[q.LHS].end() && 
					(s.dot == q.RHS.size() || q.RHS[0] == Grammar::lambda)) {
				reduce++;
				P = q;
			}
		}
		if(go_to_table[state].find(X) != go_to_table[state].end())
			shift++;
		if(reduce + shift >= 2)
			assert(false); // grammar can't use simple LR.
		if(reduce + shift == 0)
			return 0;
		if(reduce == 1) { // Reduce
			for(size_t i = 0; i < P.RHS.size(); i++) 
				tokenStk.pop(), stateStk.pop();

			tokenStk.push(P.LHS);
			state = stateStk.top();
			if(go_to_table[state].find(P.LHS) == go_to_table[state].end()) {
				return 0;
			}
			state = go_to_table[state][P.LHS];
			stateStk.push(state);
		} else { // shift
			state = go_to_table[state][X];
			stateStk.push(state);
			tokenStk.push(X);
			tokens.pop();
		}
	}
	while(!stateStk.empty()) {
		state = stateStk.top();
		X = Grammar::lambda;
#ifdef DEBUG 
		puts("");
		printf("state %d front %s\n", state, X.c_str());
		LRstates[state].print(*this);
		for (std::stack<int> dump = stateStk; !dump.empty(); dump.pop())
        	std::cout << "state stack "<< dump.top() << '\n';
		for (std::stack<string> dump = tokenStk; !dump.empty(); dump.pop())
        	std::cout << "token stack "<< dump.top() << '\n';
#endif
		int reduce = 0, shift = 0;
		Production P;
		for(set< pair<Production, ConfigurationSet::State> >::iterator it = LRstates[state].configs.begin(); 
			it != LRstates[state].configs.end(); it++) {
			Production q = it->first;
			ConfigurationSet::State s = it->second;
			if(follow_set[q.LHS].find(X) != follow_set[q.LHS].end() && 
					(s.dot == q.RHS.size() || q.RHS[0] == Grammar::lambda)) {
				reduce++;
				P = q;
			}
		}
		if(go_to_table[state].find(X) != go_to_table[state].end())
			shift++;
		if(reduce + shift >= 2)
			assert(false); // grammar can't use simple LR.
		if(reduce + shift == 0)
			return 0;
		if(reduce == 1) { // Reduce
			for(size_t i = 0; i < P.RHS.size(); i++) 
				tokenStk.pop(), stateStk.pop();

			tokenStk.push(P.LHS);
			state = stateStk.top();
			if(go_to_table[state].find(P.LHS) == go_to_table[state].end()) {
				if(P.LHS == Grammar::start_symbol)
					return 1;
				return 0;
			}
			state = go_to_table[state][P.LHS];
			stateStk.push(state);
		} else { // shift
			state = go_to_table[state][X];
			stateStk.push(state);
			tokenStk.push(X);
			tokens.pop();
		}
	}
	return 0;
}
void parsingProduction(string r, Grammar &g) {
	static int 		production_label = 0;
	stringstream 	sin(r);
	string 			lhs, foo;
	vector<string> 	tokens;
	sin >> lhs >> foo;
	while(sin >> foo)
		tokens.push_back(foo);
	Production p(lhs, tokens);
	p.label = ++production_label;
	g.rules.push_back(p);
}
bool isNumber(string str) {
	for(int i = 0; i < str.length(); i++) {
		if(!isdigit(str[i]))
			return false;
	}
	return true;
}
int scanTokens(char s[], queue<string>& tokens, vector<string>& val) {
	string keyword[18] = {"AND", "THEN", "GO", "KEEP", 
			"RIGHT", "LEFT", "FIRST", "SECOND", "THIRD", 
			"AT", "RECORD", "TIME", "TO", "KMH", "CHANGE",
			"AVERAGE", "SPEED", "CAS"};
	for(int i = 0; s[i]; i++) {
		if(s[i] == '"') {
			// s-word can't empty, and after the opening speech marks no more space.
			if(s[i + 1] == '"' || isspace(s[i + 1]))	
				return 0;
			i++;
			while(s[i] != '"') {
				if(isupper(s[i])) {}
				else if(isspace(s[i])) {s[i] = '_';}
				else if(s[i] == '.') {
					if(isspace(s[i - 1]) || s[i - 1] == '_') {
						return 0;
					}
				} else {
					return 0;
				}
				i++;
			}
			if(s[i] == '\0' || isspace(s[i - 1]) || s[i - 1] == '_')
				return 0;
		}
	}
	stringstream 	sin(s);
	string 			token;
	while(sin >> token) {
		int f = 0;
		for(int i = 0; i < 18; i++) {
			if(token == keyword[i])
				tokens.push(token), val.push_back(token), f = 1;
		}
		if(f)	continue;
		if(token[0] == '"')
			tokens.push("SIGNWORDS"), val.push_back(token), f = 1;
		if(f)	continue;
		if(isNumber(token))
			tokens.push("NNN"), val.push_back(token), f = 1;
		if(f)	continue;
		return 0;
	}
	return 1;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout);
	Grammar g;
	parsingProduction("<instruction> 	-> <navigational>", g);
	parsingProduction("<instruction> 	-> <time-keeping>", g);
	parsingProduction("<instruction> 	-> <navigational> AND <time-keeping>", g);
	parsingProduction("<navigational> 	-> <directional>", g);
	parsingProduction("<navigational> 	-> <navigational> AND THEN <directional>", g);
	parsingProduction("<directional> 	-> <how> <direction>", g);
	parsingProduction("<directional> 	-> <how> <direction> <where>", g);
	parsingProduction("<how> 			-> GO", g);
	parsingProduction("<how> 			-> GO <when>", g);
	parsingProduction("<how>			-> KEEP", g);
	parsingProduction("<direction> 		-> RIGHT", g);
	parsingProduction("<direction>		-> LEFT", g);
	parsingProduction("<when>			-> FIRST", g);
	parsingProduction("<when>			-> SECOND", g);
	parsingProduction("<when>			-> THIRD", g);
	parsingProduction("<where> 			-> AT <sign>", g);
	parsingProduction("<sign>			-> SIGNWORDS", g);
	parsingProduction("<time-keeping> 	-> <record>", g);
	parsingProduction("<time-keeping>	-> <change>", g);
	parsingProduction("<record>			-> RECORD TIME", g);
	parsingProduction("<change>			-> <cas> TO NNN KMH", g);
	parsingProduction("<cas>			-> CHANGE AVERAGE SPEED", g);
	parsingProduction("<cas> 			-> CAS", g);
	g.start_symbol = "<instruction>";
		
	g.fill_first_set();
	g.fill_follow_set();
	g.build_CFSM();
	
	char 	line[1024];
	int 	cases = 0;
	while(gets(line)) {
		if(!strcmp(line, "#"))
			break;
		queue<string> tokens;
		vector<string> val;
		int f = scanTokens(line, tokens, val);
		printf("%3d.", ++cases);
		if(!f) {
			puts(" Trap!");
			continue;
		}
		f = g.slr1driver(tokens);
		if(!f) {
			puts(" Trap!");
			continue;
		}
		for(int i = 0; i < val.size(); i++) {
			if(val[i][0] == '"')
				for(int j = 0; j < val[i].length(); j++)
					if(val[i][j] == '_')
						val[i][j] = ' ';
			printf(" %s", val[i].c_str());
		}
		puts("");
	}
	return 0;
}
