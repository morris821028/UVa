#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1048576<<1;
const long long MOD = 1e+9 + 7;
class SegmentTree {
public:
    struct Node {
        long long mul;
        void init() {}
    } nodes[MAXN];
    void pushDown(int k, int l, int r) {
        
    }
    void pushUp(int k) {
        nodes[k].mul = (nodes[k<<1].mul * nodes[k<<1|1].mul) % MOD;
    }
    void build(int k, int l, int r, long long A[]) { 
        nodes[k].init();
        if (l == r) {
            nodes[k].mul = A[l];
            return ;
        }
        int mid = (l + r)/2;
        build(k<<1, l, mid, A);
        build(k<<1|1, mid+1, r, A);
        pushUp(k);
    } 
    // query 
    long long r_mul;
    void qinit() {
        r_mul = 1;
    }
    void query(int k, int l, int r, int x, int y) {
        if (x <= l && r <= y) {
            r_mul *= nodes[k].mul;
            r_mul %= MOD;
            return ;
        }
        pushDown(k, l, r);
        int mid = (l + r)/2;
        if (x <= mid)
            query(k<<1, l, mid, x, y);
        if (y > mid)
            query(k<<1|1, mid+1, r, x, y);
    }
} tree;


long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x) % mod;
		y >>= 1, x = (x * x) % mod;
	}
	return ret;
}
static long long A[MAXN];

int main() {
	int N, P;
	int x, l, r, Q;
	while (scanf("%d %d", &N, &P) == 2) {
		for (int i = 1; i <= N; i++) {
			scanf("%d", &x);
			A[i] = (mpow(P, x, MOD) + 1)%MOD;
		}
		tree.build(1, 1, N, A);
		
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &l, &r);
			tree.qinit();
			tree.query(1, 1, N, l, r);
			long long ret = (tree.r_mul + MOD-1)%MOD;
			printf("%lld\n", ret);
		}
	}
	return 0;
}
/*
4  2
3  5  2  7
2
1  3
1  4
*/
