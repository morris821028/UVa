#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, long long> Doll;
int main() {
	int N, K, cases = 0;
	while (scanf("%d %d", &N, &K) == 2) {
		if (N == 0 && K == 0)
			return 0;
		vector<Doll> A;
		for (int i = 0; i < N; i++) {
			int s, p;
			scanf("%d %d", &s, &p);
			A.push_back(make_pair(s, p));
		}
		sort(A.begin(), A.end());
		int Ssize = 0;
		double ret = 1e+30;
		long long mx = 0, sum = 0;
		for (int i = 0; i < N; i++) {
			if (Ssize >= K-1) {
				// [WARNING] don't use (\sum{size} / size_max) * price_max
				ret = min(ret, (double) sum * A[i].second / A[i].first + A[i].second);
			}
			if (Ssize < K-1) {
				sum += A[i].first;
				Ssize++;
			}
		}
		printf("Case #%d: %.6lf\n", ++cases, ret);
	}
	return 0;
}

