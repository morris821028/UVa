#include <bits/stdc++.h>
using namespace std;
const int mod = 10007;
char s[1048576], suff[1048576];
int priority(char c) {
	switch (c)  {
		case '(': return 0;
		case '+': return 1;
		case '*': return 2;
	}
}
int main() {
	int L;
	while (scanf("%d %s", &L, s+1) == 2) {
		stack< pair<int, int> > dp;
		stack<char> stk;
		s[0] = '(', s[L+1] = ')', s[L+2] = '\0';
		int n = 0;
		for (int i = 0; s[i]; i++) {
			if (s[i] != '(') {
				if (i == 0 || s[i-1] != ')')
					suff[n++] = '_';
			}
			if (s[i] == ')') {
				while (!stk.empty() && stk.top() != '(')
					suff[n++] = stk.top(), stk.pop();
				stk.pop();
			} else {
				if (s[i] != '(') {
					while (!stk.empty() && priority(stk.top()) > priority(s[i]))
						suff[n++] = stk.top(), stk.pop();
				}
				stk.push(s[i]);
			}
		}
		while (!stk.empty())
			suff[n++] = stk.top(), stk.pop();
		suff[n] = '\0';
//		puts(suff);
		dp.push({1, 1});
		for (int i = 0; i < n; i++) {
			if (suff[i] == '_') {
				dp.push({1, 1});
			} else {
				pair<int, int> a, b, c;
				b = dp.top(), dp.pop();
				a = dp.top(), dp.pop();
				if (suff[i] == '+') {
					c.first = (a.first*b.first)%mod;
					c.second = (((a.first+a.second)*(b.first+b.second)%mod - c.first)%mod + mod)%mod;
				} else {
					c.second = (a.second*b.second)%mod;
					c.first = (((a.first+a.second)*(b.first+b.second)%mod - c.second)%mod + mod)%mod;
				}
				dp.push(c);
			}
		}
		printf("%d\n", dp.top().first);
	}
	return 0;
}
/*
4
+(*)
4
++++
4
+*+*
7 
+*+**++ 
9 
+*+(**++) 
5
***+*
*/

