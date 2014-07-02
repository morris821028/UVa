#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <map>
using namespace std;

#define MAXN 5024288
#define INF 0x3f3f3f3f
long long A[MAXN], SM[MAXN], SB[MAXN];
// binary index tree
int BIT[MAXN<<1];
void modify(int x, int v, int L) {
	while(x <= L) {
		BIT[x] = max(BIT[x], v);
		x += x&(-x);
	}
}
int query(int x) {
	int ret = - INF;
	while(x) {
		ret = max(ret, BIT[x]);
		x -= x&(-x);
	}
	return ret;
}
int main() {
	int testcase, N, X;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &X);
		for(int i = 1; i <= N; i++)
			scanf("%lld", A+i);
		
		for(int i = 1; i <= N; i++)
			SM[i] = SM[i-1] + A[i];
		for(int i = 0; i <= N; i++)
			SB[i] = SM[i];
		for(int i = 1; i <= N + 1; i++)
			BIT[i] = - INF;
		sort(SB, SB + N + 1);

		int M = unique(SB, SB + N + 1) - SB;		
		int ret = INF;
		for(int i = 0; i <= N; i++) {
			long long v = SM[i] - X;
			int pos = upper_bound(SB, SB + M, v) - SB;
			if(pos - 1 >= 0 && i)  {
				ret = min(ret, i - query(pos));
//				printf("query %d\n", i - query(pos));
			}
			pos = upper_bound(SB, SB + M, SM[i]) - SB;
			modify(pos, i, M);
//			printf("%lld %d\n", v, pos);
		}
		
		printf("%d\n", ret == INF ? -1 : ret);
	}
	return 0;
}
/*
3
5 4
1 2 1 2 1
6 -2
-5 -6 -7 -8 -9 -10
5 3
-1 1 1 1 -1
*/
