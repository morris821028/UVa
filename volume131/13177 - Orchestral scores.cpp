#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, p;
	while (scanf("%d %d", &p, &n) == 2) {
		static int A[131072];
		int l = 1, r = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &A[i]);
			r = max(r, A[i]);
		}
		int ret = 1;
		while (l <= r) {
			int m = (l+r)/2;
			int need = 0;
			for (int i = 0; i < n; i++)
				need += (A[i]+m-1)/m;
			if (need <= p)
				r = m-1, ret = m;
			else
				l = m+1;
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
4  4
8  5  5  2
6  4
8  5  5  2
7  4
8  5  5  2
*/
