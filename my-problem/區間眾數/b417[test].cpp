#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
const int MAXV = 100005;
const int MAXQ = 1000005;
const int MAXSQRTV = 512;

int A[MAXN], B[MAXN];
int main() {
	int n, m, l, r, a, b;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &l, &r);
			for (int j = l, k = 0; j <= r; k++, j++)
				B[k] = A[j];
			int t = r - l + 1;
			sort(B, B+t);
			int mx = 0, mx2 = 0, cnt = 1;
			for (int j = 1; j <= t; j++) {
				if (j == t || B[j] != B[j-1]) {
					if (cnt > mx)
						mx = cnt, mx2 = 0;
					if (cnt == mx)
						mx2++;
					cnt = 1;
				} else {
					cnt++;
				}
			}
			printf("%d %d\n", mx, mx2);
		}
	}
	return 0;
}

