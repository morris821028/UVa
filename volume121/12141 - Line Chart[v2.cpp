#include <stdio.h> 
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <assert.h>
using namespace std;

#define MAXN 10050
int dp[MAXN][64][3] = {};
int UBIT[64][3][MAXN], DBIT[64][3][MAXN];
int shift[64][3][MAXN] = {};
const int mod = 1000000;
int query(int A[], int idx) {
	int sum = 0;
	while (idx)
		sum = (sum + A[idx])%mod, idx -= idx&(-idx);
	return sum;
}
void modify(int A[], int idx, int val, int L) {
	while (idx <= L)
		A[idx] = (A[idx] + val)%mod, idx += idx&(-idx);
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout);
	int testcase, n, m, x, y;
	int cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		vector< pair<int, int> > D;
		map<int, int> R;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			R[y] = 0;
			D.push_back(make_pair(x, y));
		}
		sort(D.begin(), D.end());
		int L = 1;
		for (map<int, int>::iterator it = R.begin();
			it != R.end(); it++)
			it->second = L++;
		for (int i = 0; i < n; i++)
			D[i].second = R[D[i].second];
		memset(UBIT, 0, sizeof(UBIT));
		memset(DBIT, 0, sizeof(DBIT));
		memset(shift, 0, sizeof(shift));		
		int used[10005] = {};
		for (int i = 0; i < n; i++) {
			if (used[D[i].second] == 0) {
				shift[0][0][D[i].second] = -1; // =
				used[D[i].second] = 1;
			}
		}
		modify(UBIT[0][1], 1, 1, L);
		modify(UBIT[0][2], 1, 1, L);
		int ret = 0;
		if (m == 0)
			ret++;
		for (int i = 0; i < n; i++) {
			for (int k = 0; k <= m; k++) {
				int dp0 = query(UBIT[k][0], D[i].second) + query(DBIT[k][0], L - D[i].second-1) - shift[k][0][D[i].second];
				int dp1 = query(UBIT[k][1], D[i].second) + query(DBIT[k][1], L - D[i].second-1) - shift[k][1][D[i].second];
				int dp2 = query(UBIT[k][2], D[i].second) + query(DBIT[k][2], L - D[i].second-1) - shift[k][2][D[i].second];
//				printf("[%d %d] %d %d %d\n", i, k, dp0, dp1, dp2);
				dp0 %= mod, dp1 %= mod, dp2 %= mod;
				shift[k][0][D[i].second] += dp0;
				shift[k][1][D[i].second] += dp1;
				shift[k][2][D[i].second] += dp2;
				if (k == m)		ret = (ret + dp0)%mod;
				if (dp2) {
					modify(UBIT[k][0], D[i].second+1, dp2, L);
					modify(UBIT[k+1][1], D[i].second+1, dp2, L);
					modify(UBIT[k][2], D[i].second+1, dp2, L);
				}
				if (dp1) {
					modify(DBIT[k][0], L - D[i].second, dp1, L);
					modify(DBIT[k][1], L - D[i].second, dp1, L);
					modify(DBIT[k+1][2], L - D[i].second, dp1, L);
				}
			}
		}
		printf("Case %d: %d\n", ++cases, (ret + mod)%mod);
	}
	return 0;
}
/*
3
3 0
1 1
2 1
3 1

3 1
101 3
102 2
104 4

3
6 1
320 3
306 1
401 3
325 4
393 5
380 2
4 1
101 3
102 2
103 2
104 4
3 0
102 2
101 1
103 3
*/
