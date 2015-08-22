#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 65536;
const long long MOD = 1000000007;
int main() {
	int N, Q, M, A[65536];
	int L, R, K;
	while (scanf("%d %d", &N, &Q) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
		
		for (int i = 0; i < Q; i++) {
			scanf("%d %d %d", &L, &R, &K);
			long long ret = 1, cnt = 0;
			for (int j = L; j <= R; j++) {
				if (A[j] <= K)
					ret = (ret * A[j])%MOD, cnt++;
			}
			if (cnt == 0)	ret = 0;
			printf("%lld %lld\n", cnt, ret);
		}
	}
	return 0;
}
/*
7 4
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3
4 6 6
*/
