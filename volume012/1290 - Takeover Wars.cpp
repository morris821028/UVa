#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
int64_t a[MAXN], b[MAXN];
int main() {
	int n, m;
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%lld", &a[i]);
		for (int i = 0; i < m; i++)
			scanf("%lld", &b[i]);
		sort(a, a+n, greater<int64_t>());
		sort(b, b+m, greater<int64_t>());
		
		int idxA = 0, idxB = 0;
		int round = 0;
		while (idxA < n && idxB < m) {
			round++;
			if (round&1) {
				if (a[idxA] < b[idxB]) {
					if (idxA < n-1)
						a[idxA+1] += a[idxA], idxA++;
				} else if (idxA < n-1 && idxB < m-1 && a[idxA] + a[idxA+1] > b[idxB] + b[idxB+1]) {
					a[idxA+1] += a[idxA], idxA++;
				} else {
					idxB++;
				}
			} else {
				if (a[idxA] > b[idxB]) {
					if (idxB < m-1)
						b[idxB+1] += b[idxB], idxB++;
				} else if (idxA < n-1 && idxB < m-1 && a[idxA] + a[idxA+1] < b[idxB] + b[idxB+1]) {
					b[idxB+1] += b[idxB], idxB++;
				} else {
					idxA++;
				}
			}
		}
		
		printf("Case %d: ", ++cases);
		if (idxA < n)
			puts("Takeover Incorporated");
		else
			puts("Buyout Limited");
	}
	return 0;
}

/*
3 2
7 1 1
5 5 

4 2
3 3 3 3
5 5

5 7
2 3 80 90 100
1 1 85 85 88 92 95
*/
