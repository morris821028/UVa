#include <bits/stdc++.h>
using namespace std;
#define MAXN 1024
int BIT[MAXN];
int query(int x) {
	int ret = -0x3f3f3f3f;
	while (x > 0) {
		ret = max(ret, BIT[x]);
		x -= x&(-x);
	}
	return ret;
}
void update(int x, int val) {
	while (x < MAXN) {
		BIT[x] = max(BIT[x], val);
		x += x&(-x);
	}
}
int main() {
	int N, C, x;
	while (scanf("%d %d", &N, &C) == 2) {
		for (int i = 0; i < MAXN; i++)
			BIT[i] = -0x3f3f3f3f;
		int ret = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d", &x);
			int v = query(x-C);
			ret = max(ret, v+(x-C));	// sell
			update(x, ret-x);			// buy
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
6 10
100 120 130 80 50 40
5 10
70 80 50 40 50
13 30
10 80 20 40 30 50 40 60 50 70 60 10 200
*/
