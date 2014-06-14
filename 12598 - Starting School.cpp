#include <stdio.h>
#include <algorithm>
using namespace std;
int A[65536], B[65536], C[65536], D[65536];
int main() {
	int testcase, cases = 0, N, K, Q;
	int x, l, r;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d", &N, &K, &Q);
		for(int i = 1; i <= K; i++)
			scanf("%d", &A[i]), B[i] = A[i];
		sort(B + 1, B + 1 + K);
		B[0] = 0, B[K+1] = N + 1;
		int M = 1;
		C[0] = 0;
		for(int i = 1; i <= K + 1; i++) {
			l = B[i - 1] + 1, r = B[i] - 1;
			if(l <= r) {
				C[M] = C[M - 1] + r - l + 1;
				D[M] = l;
				M++;
			}
		}
		printf("Case %d:\n", ++cases);
		while(Q--) {
			scanf("%d", &x);
			if(x <= K)
				printf("%d\n", A[x]);
			else {
				x -= K;
				int pos = lower_bound(C, C + M, x) - C;
				printf("%d\n", D[pos] + x - C[pos-1] - 1);
			}
		}
	}
	return 0;
}
/*
2
10 4 4
1 3 5 2
5 6 9 10
10 3 2
10 1 9
4 10
*/
