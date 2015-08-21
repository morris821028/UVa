#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
int A[MAXN], R[MAXN];
int main() {
	int N, Q;
	int cmd, l, r, x;
	while (scanf("%d %d", &N, &Q) == 2) {
		if (N >= MAXN)	return 0;
		for (int i = 1; i <= N; i++)
			A[i] = i, R[i] = i;
		for (int i = 0; i < Q; i++) {
			scanf("%d", &cmd);
			if (cmd == 0) {
				scanf("%d %d", &l, &r);
				reverse(A+l, A+r+1);
				for (int j = l; j <= r; j++)
					R[A[j]] = j;
			} else {
				scanf("%d", &x);
				printf("%d\n", R[x]);
			} 
		}
	}
	return 0;
}
