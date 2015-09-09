#include <bits/stdc++.h>
using namespace std;
const int MAXN = 524288;
const int MAXLOGN = 20;
class SparseTableRMQ {
public:
	int A[MAXN], fa[MAXLOGN][MAXN];
	void build(int n) {
		for (int i = 0; i <= n; i++)
			fa[0][i] = i;
		for (int i = 1; (1<<i) <= n; i++) {
			for (int j = 0; i+j <= n; j++) {
				int a = fa[i-1][j], b = fa[i-1][j+(1<<(i-1))];
				fa[i][j] = A[a] > A[b] ? a : b;
			}
		}
	}
	int query(int l, int r) {	// return maximum position
		int p = __builtin_clz((int)1) - __builtin_clz(r-l+1);
		int a = fa[p][l], b = fa[p][r-(1<<p)+1];
		return A[a] > A[b] ? a : b;
	}
} TT;
void compute(int N, int K, int L, int R) {
	struct E {
		int l, L, R, t;
		E(int a = 0, int b = 0, int c = 0, int d = 0):
			l(a), L(b), R(c), t(d) {}
		bool operator<(const E &x) const {
			return TT.A[t] - TT.A[l-1] > TT.A[x.t] - TT.A[x.l-1];
		}
	};
	
	multiset<E> S;
	for (int i = 1; i <= N; i++) {
		if (i+L-1 <= N) {
			int l = i+L-1, r = min(i+R-1, N);
			E e = E(i, l, r, TT.query(l, r));
			S.insert(e);
		}
	}
	
	long long ret = 0;
	for (int i = 0; i < K; i++) {
		E e = *S.begin();
		S.erase(S.begin());
		ret += TT.A[e.t] - TT.A[e.l-1];
		
		if (e.t-1 >= e.L)
			S.insert(E(e.l, e.L, e.t-1, TT.query(e.L, e.t-1)));
		if (e.t+1 <= e.R)
			S.insert(E(e.l, e.t+1, e.R, TT.query(e.t+1, e.R)));
	}
	printf("%lld\n", ret);
}
int main() {
	int N, K, L, R;
	while (scanf("%d %d %d %d", &N, &K, &L, &R) == 4) {
		for (int i = 1, s = 0, x; i <= N; i++) {
			scanf("%d", &x);
			s += x, TT.A[i] = s;
		}
		TT.build(N);
		compute(N, K, L, R);
	}
	return 0;
}

