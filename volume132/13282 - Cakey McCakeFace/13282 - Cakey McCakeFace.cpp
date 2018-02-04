/**
TLE
*/
#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 32767;
int A[MAXN], B[MAXN];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < m; i++)
			scanf("%d", &B[i]);
		map<int, int> R;
		for (int i = 0, st = 0; i < n; i++) {
			while (st < m && B[st] <= A[i])
				st++;
			int v = A[i];
			for (int j = st; j < m; j++)
				R[B[j]-v]++;
		}

		int mx = 0, ret = 0;
		for (auto e : R) {
			if (e.second >  mx)
				mx = e.second, ret = INT_MAX;
			if (e.second == mx)
				ret = min(ret, e.first);
				
		}
		printf("%d\n", ret);
	}
	return 0;
}
