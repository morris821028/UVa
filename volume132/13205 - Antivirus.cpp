#include <bits/stdc++.h>
using namespace std;

const int MAXN = 524288;

int32_t stMin(int32_t x, int32_t y) {return min(x, y);}
int64_t stSum(int64_t x, int64_t y) {return x + y;}

template <class ETYPE>
class zkwST {
public:
	ETYPE tree[(MAXN<<1) + 10];
	ETYPE fi;
	ETYPE (*fm) (ETYPE, ETYPE);
	int M;
	void init(ETYPE (*fm) (ETYPE, ETYPE), ETYPE fi) {
		this->fm = fm;
		this->fi = fi;
	}
	void initTree(int n, ETYPE A[]) {	/* A[1...n] */
	 	for (M = 1; M < n; M <<= 1);
	    for (int i = 2*M - 1; i >= 0; i--) {
	    	if (i >= M) {
	    		tree[i] = A[i-M];
			} else {
				tree[i] = fm(tree[i<<1], tree[i<<1|1]);
			}
	    }
	}
	
	ETYPE query(int s, int t) {
		ETYPE ret = fi;
		if (s > t)
			return ret;
	    for (s = s + M - 1, t = t + M + 1; (s^t) != 1;) {
	        if (~s&1)
	            ret = fm(ret, tree[s^1]);
	        if (t&1)
	            ret = fm(ret, tree[t^1]);
	        s >>= 1, t >>= 1;
	    }
	    return ret;
	}
	
	void update(int s, ETYPE v) {
	    tree[s + M] = v;
	    for (s = (s + M)>>1; s > 0; s >>= 1)
	        tree[s] = fm(tree[s<<1], tree[s<<1|1]);
	}
};

zkwST<int32_t> tMp, tMm;
zkwST<int64_t> tSm;

int main() {
	tMp.init(stMin, (int32_t) INT_MAX);	// A[]+index
	tMm.init(stMin, INT_MAX);	// A[]-index
	tSm.init(stSum, 0);			// A[]
	int n, q;
	static int32_t A[MAXN], B[MAXN];
	static int64_t C[MAXN];
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		
		for (int i = 1; i <= n; i++) 
			B[i] = A[i]+i;
		tMp.initTree(n, B);
		for (int i = 1; i <= n; i++) 
			B[i] = A[i]-i;
		tMm.initTree(n, B);
		for (int i = 1; i <= n; i++) 
			C[i] = A[i];
		tSm.initTree(n, C);
		
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			int cmd, row, val;
			scanf("%d %d %d", &cmd, &row, &val);
			if (cmd == 1) {
				tMp.update(row, val+row);
				tMm.update(row, val-row);
				tSm.update(row, val);
				A[row] = val;
			} else {
				int64_t l = 1, r = A[row], mid;
				if (val == 1)
					r = min(min(r, (int64_t) row), (int64_t) n-row+1);
				int64_t ret = 0;
//				printf("\nA[]   ");
//				for (int i = 1; i <= n; i++)
//					printf("%3d ", A[i]);
//				printf("\nA[]-i ");
//				for (int i = 1; i <= n; i++)
//					printf("%3d ", A[i]-i);
//				printf("\nA[]+i ");
//				for (int i = 1; i <= n; i++)
//					printf("%3d ", A[i]+i);
//				puts("");
				while (l <= r) {
					mid = (l+r)/2;
					int64_t t1 = tMm.query(max(row-mid+1, (int64_t) 1), row-1);
					if (t1 >= mid-row) {
						l = mid+1, ret = mid;
					} else { 
						r = mid-1;
					} 
				}
				
				l = 1, r = ret;
				while (l <= r) {
					mid = (l+r)/2;
					int64_t t2 = tMp.query(row+1, min(row+mid-1, (int64_t) n));
					if (t2 >= mid+row) {
						l = mid+1, ret = mid;
					} else { 
						r = mid-1;
					} 
				}
				
				l = max(row-ret+1, (int64_t) 1), r = min(row+ret-1, (int64_t) n);
				int64_t lpart = ret-(row-l);
				int64_t rpart = ret-(r-row);
				int64_t t3 = tSm.query(l, r)
							- (lpart+ret)*(ret-lpart+1)/2 
							- (rpart+ret-1)*(ret-rpart)/2;
				printf("%lld %lld\n", ret, t3);
			}
		}
	}
	return 0;
}
/*
12
3  4  5  5  6  2  5  4  3  2  1  1
9
2  6  0
2  6  1
2  4  0
2  4  1
1  6  6
2  6  0
2  6  1
2  4  0
2  4  1
*/
