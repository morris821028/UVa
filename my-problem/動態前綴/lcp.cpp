#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;
const long long mod = 100000007LL;
#define MAXN (1<<17)
char S[MAXN];
long long base[MAXN];
long long tree[MAXN<<1];
long long build(int k, int l, int r) {
	assert(l <= r);
	if (l == r)
		return tree[k] = (S[l] % mod);
	int m = (l + r)/2;
	build(k<<1, l, m);
	build(k<<1|1, m+1, r);
	tree[k] = (tree[k<<1] * base[r - m] + tree[k<<1|1]) %mod;
}
void modify(int k, int l, int r, int x, int v) {
	if (l == r) {
		tree[k] = v;
		return;
	}
	int m = (l + r)/2;
	if (x <= m)
		modify(k<<1, l, m, x, v);
	else
		modify(k<<1|1, m+1, r, x, v);
	tree[k] = (tree[k<<1] * base[r - m]%mod + tree[k<<1|1]) %mod;
}
long long query(int k, int l, int r, int x, int y) {
	assert(l >= 0 && l <= r);
	if (x <= l && r <= y) {
//		printf("[%d %d] %lld\n", l, r, tree[k]);
		return tree[k];
	}
	int m = (l + r)/2;
	if (y <= m)
		return query(k<<1, l, m, x, y);
	else if(x > m)
		return query(k<<1|1, m+1, r, x, y);
	else {
		long long p, q;
		p = query(k<<1, l, m, x, y);
		q = query(k<<1|1, m+1, r, x, y);
//		printf("query merge %d %d %lld %lld %lld\n", y, m, base[y-m], p, q);
		return (p * base[min(y, r) - m]%mod + q) %mod;
	}
}
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout); 
	base[0] = 1;
	for (int i = 1; i < MAXN; i++) 
		base[i] = (base[i-1] * 63689)%mod;
	char cmd[8], s[8];
	int Q, p, q, n;
	while (scanf("%s", S) == 1) {
		n = strlen(S);
		build(1, 0, n - 1);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%s", cmd);
			if (cmd[0] == 'Q') {
				scanf("%d %d", &p, &q);
				if (p == q) {
					printf("%d\n", n - p);
					continue;
				} else if (S[p] != S[q]) {
					puts("0");
					continue;
				}
				int l = 0, r = min(n - p, n - q) - 1, m, ret = 0;
				long long hp, hq;
				while (l <= r) {
					m = (l + r)/2;
					hp = query(1, 0, n-1, p, p + m);
					hq = query(1, 0, n-1, q, q + m);
					if (hp == hq)
						l = m + 1, ret = m;
					else
						r = m - 1;
				}
				printf("%d\n", ret + 1);
//				printf("%s %s %d %lld %lld\n", S + p, S + q, r, query(1, 0, n-1, p, p+2), query(1, 0, n-1, q, q+2));
			} else {
				scanf("%d %s", &p, s);
				S[p] = s[0];
				modify(1, 0, n - 1, p, s[0]);
			}
		}
	}
	return 0;
}
/*
abcdabcc
3
Q 0 4
C 3 c
Q 0 4
*/ 
