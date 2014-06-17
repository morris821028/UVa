#include <stdio.h> 
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <ctype.h>
#include <assert.h>
using namespace std;

class Production {
	public:
		string 			LHS;
		vector<string> 	RHS;
		int 			label;
		
		Production(string L = "", vector<string> R = vector<string>()) {
			LHS = L;
			RHS = R;
		}
		
		void print() {
			printf("%s -> ", LHS.c_str());
			for(size_t i = 0; i < RHS.size(); i++)
				printf("%s", RHS[i].c_str());
		}
};
class Grammar {
	public:
		static const string 		lambda;
		string 						start_symbol;
		vector<Production> 			rules;
		map<string, set<string> > 	first_set;
		map<string, set<string> > 	follow_set;
		map<string, bool> 			derives_lambda;
		map<string, map<string, Production> >	lltable;
		
		map<string, bool> mark_lambda();
		void fill_first_set();
		void fill_follow_set();
		bool isNonterminal(string token);
		set<string> compute_first(vector<string> rhs);
		set<string> get_predict_set(Production p);
		void fill_lltable();
		void lldriver(queue<string> tokens);
};
const string Grammar::lambda("l");

set<string> Grammar::compute_first(vector<string> rhs) {
	set<string> result;
	size_t i;
	
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
bool Grammar::isNonterminal(string token) {
	
	if(token[0] == '<' && token[token.length() - 1] == '>')
		return true;
	return false;

}
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
int aVowel(char c) {
	switch(c) {
		case 'a':case 'e':case 'i':case 'o':case 'u':
			return 1;
	}
	return 0;
}
string token2symbol(const string &str) {
    int n = str.length();
    if (!islower(str[n - 1]) || !aVowel(str[n - 1])) {
        return "NAM";
    }
    switch (n) {
    	case 1: return "A";
    	case 5:
        n = aVowel(str[4]);
        n |= ((aVowel(str[0]) << 4) | (aVowel(str[1]) << 3));
        n |= ((aVowel(str[2]) << 2) | (aVowel(str[3]) << 1));
        return (n == 5 || n == 9) ? "PREDA" : "UN";
    	case 2:
        	switch (str[0]) {
        		case 'g': return "MOD";
        		case 'b': return "BA";
        		case 'd': return "DA";
        		case 'l': return "LA";
        	}
    }
    return "UN";
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

int main() {
	Grammar g;
	parsingProduction("<sentence>    ->  <common_pre>", g);
	parsingProduction("<sentence>    ->  DA <preds>", g);
	parsingProduction("<common_pre>  ->  <predname> <suffix>", g);
	parsingProduction("<suffix>      ->  <predclaim>", g);
	parsingProduction("<suffix>	  	 ->  <statement>", g);
	parsingProduction("<predclaim>   ->  BA <preds>", g);
	parsingProduction("<predclaim>   ->  DA <preds>", g);
	parsingProduction("<preds>       ->  <preds_head> <preds_tail>", g);
	parsingProduction("<preds_head>  ->  <predstring>", g);
	parsingProduction("<preds_tail>  ->  A <predstring> <preds_tail>", g);
	parsingProduction("<preds_tail>  ->  l", g);
	parsingProduction("<predname>    ->  LA <predstring>", g);
	parsingProduction("<predname>    ->  NAM", g);
	parsingProduction("<predstring>  ->  PREDA <predstr_tail>", g);
	parsingProduction("<predstr_tail> -> PREDA <predstr_tail>", g);
	parsingProduction("<predstr_tail> -> l", g);
	parsingProduction("<statement>   ->  <verbpred> <statement_s>", g);
	parsingProduction("<statement_s> ->  <predname>", g);
	parsingProduction("<statement_s> ->  l", g);
	parsingProduction("<verbpred>    ->  MOD <predstring>", g);
	
	g.start_symbol = "<sentence>";
		
	g.fill_first_set();
	g.fill_follow_set();
	g.fill_lltable();
	
	queue<string> SYMBOL;
	for(string token; cin >> token && token != "#";) {
		size_t pos = token.find('.');
		if(pos == string::npos) {
			SYMBOL.push(token2symbol(token));
			//cout << token2symbol(token) << " ";
			continue;
		}
		token.erase(token.length() - 1);
		//cout << token2symbol(token) << endl;
		if(token.length() > 0)
			SYMBOL.push(token2symbol(token));
		g.lldriver(SYMBOL);
		
		while(!SYMBOL.empty())
			SYMBOL.pop();
	}
	return 0;
}
