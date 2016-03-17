#include <bits/stdc++.h>
using namespace std;

int main() {
	vector<unsigned long long> ret;
	unsigned long long a = 0;
	for (int N = 1; N <= 64; N++) {
		a = a<<1 | 1;
		for (int M = 1; M <= 64; M++) {
			unsigned long long v = a;
			for (int i = N; i <= 64; i += N + M) {
				ret.push_back(v);
				v = v << M;
				v = v << N | a;
			}
			v = a << M;
			for (int i = N+M; i <= 64; i += N + M) {
				ret.push_back(v);
				v = v << N | a;
				v = v << M;
			}
		}
	}
	sort(ret.begin(), ret.end());
	ret.resize(unique(ret.begin(), ret.end()) - ret.begin());
	unsigned long long L, R;
	while (scanf("%llu %llu", &L, &R) == 2) {
		int sum = 0;
		for (auto x : ret) {
			sum += x >= L && x <= R;
		}
		printf("%d\n", sum);
	}
	return 0;
}

