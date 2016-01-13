#include <bits/stdc++.h>
using namespace std;

const int MAXN = 131072;
int N;
long long P, B[MAXN], C[MAXN];
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %lld", &N, &P);
		for (int i = 1; i <= N; i++)
			scanf("%lld", &B[i]);
		C[0] = 0;
		for (int i = 1; i <= N; i++)
			C[i] = C[i-1] + B[i];
			
		long long ret = 0;
		for (int i = 1; i <= N; i++) {
			int idx = (int) (lower_bound(C, C + N+1, C[i] - P) - C);
			ret += i - idx;
		}
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}

