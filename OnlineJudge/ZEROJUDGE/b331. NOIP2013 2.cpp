#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 16777216;
char s[MAXN];
int main() {
	fgets(s, MAXN, stdin);
	int n = strlen(s)-1, op = 0;
	stack<long long> stk;
	for (int i = 0; i < n; ) {
		if (s[i] == '+')
			op = 0, i++;
		else if (s[i] == '*')
			op = 1, i++;
		else {
			long long x = 0;
			while (isdigit(s[i]))
				x = x * 10 + s[i] - '0', i++;
			x %= 10000;
			if (op == 0) {
				stk.push(x);
			} else {
				x = (x * stk.top())%10000;
				stk.pop();
				stk.push(x);
			}
		}
	}
	
	long long ret = 0;
	while (!stk.empty())
		ret = (ret + stk.top())%10000, stk.pop();
	printf("%lld\n", ret);
	return 0;
}
