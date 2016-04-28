#include <bits/stdc++.h>
using namespace std;
// Algorithm: Meet in Middle
const int MAXN = 85;
const long long MAXV = 1e+18;
long long F[100] = {2, 3};
vector<long long> S1, S2;
void bfs(int begin, int end, vector<long long> &S) {
	S.push_back(1);
	for (int i = begin; i < end; i++) {
		long long x = F[i];
		vector<long long> next(S);
		for (auto e : S) {
			while (MAXV / e / x) {
				e *= x;
				next.push_back(e);
			}
		}
		S = next;
	}
	sort(S.begin(), S.end());
  	S.resize(unique(S.begin(), S.end()) - S.begin());
}

int main() {
	for (int i = 2; i < MAXN; i++) {
		F[i] = F[i-1] + F[i-2];
		assert(F[i] / MAXV == 0);
	}
	int split = 6;
	bfs(0, split, S1);
	bfs(split, MAXN, S2);
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		long long a, b;
		long long ret = -1;
		scanf("%lld %lld", &a, &b);
		int idx1 = 0, idx2 = S2.size()-1;
		for (; idx1 < S1.size(); idx1++) {
			if (S1[idx1] > b)	break;
			long long e = S1[idx1];
			while (idx2 > 0 && b / S2[idx2] / e == 0)
				idx2--;
			long long t = S2[idx2] * e;
			if (t >= a)
				ret = max(ret, t);
		}
		vector<long long>::iterator it = lower_bound(S1.begin(), S1.end(), b);
		if (it == S1.end() || it != S1.begin() && *it > b)	it--;
		if (it != S1.end() && b / *it) {
			long long t = *it;
			if (t >= a)
				ret = max(ret, t);
		}
		it = lower_bound(S2.begin(), S2.end(), b);
		if (it == S2.end() || it != S2.begin() && *it > b)	it--;
		if (it != S2.end() && b / *it) {
			long long t = *it;
			if (t >= a)
				ret = max(ret, t);
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
1
5231711 13073137
*/


