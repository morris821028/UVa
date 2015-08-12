#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m = 0;
	map<pair<int, pair<int, int> >, int> R;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		long long A[3];
		scanf("%lld %lld %lld", &A[0], &A[1], &A[2]);
		sort(A, A+3);
		if (A[2] >= A[0] + A[1])
			continue;
		m++;
		int g = __gcd(A[0], __gcd(A[1], A[2]));
		A[0] /= g, A[1] /= g, A[2] /= g;
		R[{A[0],{A[1], A[2]}}]++;
	}
	int ret = 0;
	for (auto &x : R)
		ret = max(ret, x.second);
	printf("%d %d\n", m, max(ret - 1, 0));
	return 0;
}
