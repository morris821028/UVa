#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector> 
using namespace std;
struct node {
	string x;
	int sign;
	node *lson, *rson;
} nodes[1024];
int nodesize;
vector< pair<string, int> > D; // <token, sign>
string var[1024];
node* dfs(string exp, int sign) {
//	printf("---- %s %d\n", exp.c_str(), sign);
	int f = 0, r = 0, div;
	for (int i = 0; i < exp.size(); i++) {
		if (exp[i] == '(')		r++;
		else if (exp[i] == ')') r--;
		else if (exp[i] == '+') {
			if (r == 0) {
				f = 1, div = i;
			}
		} else if (exp[i] == '-') {
			if (r == 0) {
				f = 1, div = i;
			}
		}
	}
	if (f) {
		node* u = &nodes[nodesize++];
		u->lson = dfs(exp.substr(0, div), sign);
		u->rson = dfs(exp.substr(div+1), sign * (exp[div] == '+' ? 1 : -1));
		u->x = string(exp[div], 1), u->sign = sign;
		return u;
	} else {
		if (exp[0] == '(') {
			return dfs(exp.substr(1, exp.length() - 2), sign);
		} else {
			node* u = &nodes[nodesize++];
			u->lson = u->rson = NULL;
			u->x = exp, u->sign = sign;
			D.push_back(make_pair(exp, sign));
			return u;
		}
	}
}
bool cmp1(pair<int, int> a, pair<int, int> b) {
	if (a.first != b.first)	return a.first > b.first;
	return a.second > b.second;
}
bool cmp2(pair<int, int> a, pair<int, int> b) {
	if (a.first != b.first)	return a.first > b.first;
	return a.second < b.second;
}
int main() {
	int testcase, cases = 0;
	char exp[1024], digit[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s %s", exp, digit);
		int n = strlen(exp), m = strlen(digit);
		nodesize = 0, D.clear();
		node *root = dfs(exp, 1);
		sort(digit, digit + m, greater<char>());
		vector< pair<int, int> > pos, neg; // <length, index>
		for (int i = 0; i < D.size(); i++) {
			if (D[i].second > 0) {
				for (int j = 0; j < D[i].first.size(); j++)
					pos.push_back(make_pair(j, i));
			} else {
				for (int j = 0; j < D[i].first.size(); j++)
					neg.push_back(make_pair(j, i));
			}
//			printf("%s %d\n", D[i].first.c_str(), D[i].second);
		}
		sort(pos.begin(), pos.end(), cmp1);
		sort(neg.begin(), neg.end(), cmp2);
		for (int i = 0; i < D.size(); i++)
			var[i] = "";
		int idx = 0;
		for (int i = 0; i < pos.size(); i++) {
			var[pos[i].second] += digit[idx];
			idx++;
		}
		idx = m - 1;
		for (int i = 0; i < neg.size(); i++) {
			var[neg[i].second] += digit[idx];
			idx--;
		}
		idx = 0;
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < n; i++) {
			if (exp[i] == '+' || exp[i] == '-' || exp[i] == '(' || exp[i] == ')')
				putchar(exp[i]);
			else {
				printf("%s", var[idx].c_str());
				idx++;
				while (exp[i] == '#')	i++;
				i--;
			}
		}
		puts("");
		long long ret = 0;
		for (int i = 0; i < D.size(); i++) {
			long long num = 0;
			for (int j = 0; j < var[i].size(); j++)
				num = num * 10 + var[i][j] - '0';
			if (D[i].second > 0)	ret += num;
			else					ret -= num;
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
99999
##-(##+###)
3333333
#+#
31
#-#
31
##+##
9191
#-#-#
123
##-((##+##)-(##+##))
1122361576
*/
