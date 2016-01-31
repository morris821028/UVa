#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, a, b;
		vector<std::pair<int, int>> A;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d %d", &a, &b), A.push_back(make_pair(b, a));
		sort(A.begin(), A.end());
		
		long long ret = 0;
		long long sum = 0;
		for (int i = n-1; i >= 0; i--) {
			sum += A[i].second;
			ret = max(ret, sum * A[i].first);
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}

