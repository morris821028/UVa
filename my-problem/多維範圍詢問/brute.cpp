#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;
int pt[8192][10], w[8192], Q[10], L[10], R[10];
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("brute_out.txt", "w+t", stdout); 
	int n, m, x, q;
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				scanf("%d", &pt[i][j]);
			scanf("%d", &w[i]);
		}
		scanf("%d", &q);
		while (q--) {
			for (int i = 0; i < m; i++)
				scanf("%d", &L[i]);
			for (int i = 0; i < m; i++)
				scanf("%d", &R[i]);
			int ww = 0, cnt = 0;
			for (int i = 0; i < n; i++) {
				int ok = 1;
				for (int j = 0; j < m && ok; j++)
					ok &= L[j] <= pt[i][j] && pt[i][j] <= R[j];
				if (ok)
					ww += w[i], cnt++;
			}
			printf("Case %d: %d %d\n", ++cases, ww, cnt);
		}
	}
	return 0;
}
