#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 2048;
int A[MAXN], B[MAXN];
struct MM {
	int dif, idx, mat;
	MM(int d=0, int i=0, int j=0):
		dif(d), idx(i), mat(j) {}
	bool operator<(const MM &t) const {
		if (dif != t.dif)	return dif < t.dif;
		return idx < t.idx;
	}
};
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < m; i++)
			scanf("%d", &B[i]);
		set<MM> S;
		for (int i = 0, st = 0; i < n; i++) {
			while (st < m && B[st] <= A[i])
				st++;
			if (st < m)
				S.insert(MM(B[st]-A[i], i, st));
		}

		int mx = 0, ret = 0;
		while (!S.empty()) {
			int t = S.begin()->dif, cnt = 0;
			while (!S.empty() && S.begin()->dif == t) {
				MM e = *S.begin();
				S.erase(S.begin());
				if (e.mat+1 < m)
					S.insert(MM(B[e.mat+1]-A[e.idx], e.idx, e.mat+1));
				cnt++;
			}
			if (cnt > mx)
				mx = cnt, ret = t;
		}
		printf("%d\n", ret);
	}
	return 0;
}
