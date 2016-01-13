#include <bits/stdc++.h>
using namespace std;

#define MAXN 2048
long long X[MAXN], Y[MAXN];
int main() {
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		long long ret = 0;
		for (int i = 0; i < n; i++)
			scanf("%lld %lld", &X[i], &Y[i]);
		
		for (int i = 0; i < n; i++) {
			map<long long, int> R;
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;
				long long dist = 0;
				dist += (X[i] - X[j])*(X[i] - X[j]);
				dist += (Y[i] - Y[j])*(Y[i] - Y[j]);
				R[dist]++;
			}
			for (auto &p : R)
				ret += p.second * (p.second-1)/2;
		}
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}

