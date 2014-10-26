#include <stdio.h> 
#include <stack>
using namespace std;

char S[131072], T[131072];
const int mod = 21092013;
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s %s", S, T);
		stack<char> stk;
		for (int i = 0; S[i]; i++) {
			if (S[i] == 'L' || S[i] == 'R')
				stk.push(S[i]);
			else if (!stk.empty())
				stk.pop();
		}
		int ret = 1, lson = 1, rson = 1;
		for (int i = 0; T[i]; i++) {
			if (T[i] == 'L')
				ret = (ret + lson)%mod, rson = (rson + lson)%mod;
			else if (T[i] == 'R')
				ret = (ret + rson)%mod, lson = (lson + rson)%mod;
			else {
				if (!stk.empty()) {
					ret = (ret + 1)%mod;
					if (stk.top() == 'L')
						rson++;
					else
						lson++;
					stk.pop();
				}
			}
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
