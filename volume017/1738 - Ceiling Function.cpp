#include <bits/stdc++.h>
using namespace std;
const int MAXN = 32;

int32_t C[MAXN][MAXN];

void ballot() {
	C[0][0] = 1;
	for (int q = 1; q < MAXN; q++) {
		for (int p = 0; p <= q; p++)
			C[p][q] = C[p][q-1] + (p-1 >= 0 ? C[p-1][q] : 0);
	}
}
int tree2type(int A[], int s) {
	static int stk[MAXN+1];
	stk[1] = INT_MIN;
	int q = s, r = 0;
	A--;
	for (int i = 1; i <= s; i++) {
		int v = A[i];
		while (stk[q+i-s] > v) {
			r = r + C[s-i][q];
			q--;
		}
		stk[q+i+1-s] = v;
	}
	return r;
}
int main() {
	ballot();
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		unordered_set<int> S;
		for (int i = 0; i < n; i++) {
			static int A[26];
			static pair<int, int> B[26];
			for (int j = 0; j < m; j++) {
				scanf("%d", &A[j]);
				B[j] = make_pair(A[j], j);
			}
			sort(B, B+m);
			for (int j = 0; j < m; j++) {
				A[j] = B[j].second;
			}
			int id = tree2type(A, m);
			S.insert(id);
		}
		int ret = S.size();
		printf("%d\n", ret);
	}
	return 0;
}
/*
5  3
2  7  1
3  1  4
1  5  9
2  6  5
9  7  3
*/

