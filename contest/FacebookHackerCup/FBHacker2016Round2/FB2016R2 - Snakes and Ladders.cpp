#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
struct State {
	int H;
	long long sum, sqsum, n;
	State(int H, long long sum = 0, 
		long long sqsum = 0, long long n = 0):
		H(H), sum(sum), sqsum(sqsum), n(n) {}
};
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, x, h;
		scanf("%d", &n);
		vector<std::pair<int, int>> A;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &h);
			A.push_back(make_pair(x, h));
		}
		sort(A.begin(), A.end());
		long long ret = 0;
		stack<State> stk;
		for (int i = 0; i < n; i++) {
			while (!stk.empty() && stk.top().H < A[i].second)
				stk.pop();
			if (!stk.empty() && stk.top().H == A[i].second) {
				State e = stk.top();
				long long X = A[i].first;
				long long N = e.n;
				long long S = N*X%MOD * X%MOD;
				S = (S - X*2%MOD*e.sum%MOD + e.sqsum)%MOD;
				e.sum = (e.sum + X)%MOD;
				e.sqsum = (e.sqsum + X*X%MOD)%MOD;
				e.n++;
				ret = (ret + S)%MOD;
				stk.pop(), stk.push(e);
			} else {
				long long X = A[i].first;
				stk.push(State(A[i].second, X, X*X%MOD, 1));
			}
		}
		ret = (ret + MOD)%MOD;
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}

