#include <bits/stdc++.h>
using namespace std;
// dp + BIT, O(n log n)
const int MAXN = 131072, MAXH = 1048576;
int A[MAXN], n;
int BIT[2][MAXH];
void modify(int BIT[], int x, int val, int dir) {
    for (; x && x < MAXH; x += (x&(-x)) * dir)
        BIT[x] = max(BIT[x], val);
}
int query(int BIT[], int x, int dir) {
	int ret = -0x3f3f3f3f;
    for (; x && x < MAXH; x += (x&(-x)) * dir)
        ret = max(ret, BIT[x]);
    return ret;
}
int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		memset(BIT, 0, sizeof(BIT));
		int ret = 0;
		for (int i = 1; i <= n; i++) {
			int U, D, x = A[i] + 1;
			U = query(BIT[0], x-1, -1) + 1;
			D = query(BIT[1], x+1, 1) + 1;
			modify(BIT[0], x, D, 1);
			modify(BIT[1], x, U, -1);
			ret = max(ret, max(U, D));
		}
		printf("%d\n", ret);
	}
	return 0;
}

