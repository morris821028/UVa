#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXN (1<<18)
#define LOGS 7
#define POWS (1<<LOGS)

int buffA[MAXN], buffB[MAXN], buffS[MAXN];
struct Node {
	int n;
	int *A, *B, *S;
	int64_t abval, lazy;
	void init(int l, int r, int I[], int *ptrA, int *ptrB, int *ptrS) {
		A = ptrA, B = ptrB, S = ptrS;
		n = 0, abval = lazy = 0;
		for (int i = l; i < r; i++)
			A[n++] = I[i], abval += abs(I[i]);
		memcpy(B, A, sizeof(A[0])*n);
		sort(B, B+n);
		for (int i = 0, s = 0; i < n; i++)
			s += B[i], S[i] = s;
	}
	inline int range(int l, int r) {
		if (r < 0)
			return 0;
		return (l ? S[r] - S[l-1] : S[r]) + lazy * (r-l+1);
	}
	void inc(int l, int r, int x) {
		if (l == 0 && r == n-1) {
			int lpos, rpos;
			if (x > 0) {
				lpos = lower_bound(B, B+n, -x-lazy) - B;
				rpos = lower_bound(B, B+n, -lazy) - B;
				abval -= lpos * x;
				abval += (n - rpos) * x;
				abval += (rpos - lpos) * (x) + 2*range(lpos, rpos-1);
			} else {
				lpos = upper_bound(B, B+n, -lazy) - B;
				rpos = upper_bound(B, B+n, -x-lazy) - B;
				abval -= lpos * x;
				abval += (n - rpos) * x;
				abval += (rpos - lpos) * (-x) - 2*range(lpos, rpos-1);
			}
			lazy += x;
			return ;
		}
		for (int i = l; i <= r; i++)
			A[i] += x;
		abval = 0;
		for (int i = 0; i < n; i++)
			A[i] += lazy, abval += abs(A[i]);
		lazy = 0;
		memcpy(B, A, sizeof(A[0])*n);
		sort(B, B+n);
		for (int i = 0, s = 0; i < n; i++)
			s += B[i], S[i] = s;
	}
	inline int brute(int l, int r) {
		int ret = 0;
		for (int i = l; i <= r; i++)
			ret += abs(A[i]+lazy);
		return ret;
	}
} nodes[MAXN/POWS];
int64_t sum_abs(int l, int r) {
	if ((l>>LOGS) == (r>>LOGS))
		return nodes[l>>LOGS].brute(l&(POWS-1), r&(POWS-1));
	int64_t ret = 0;
	if (l&(POWS-1)) {
		ret += nodes[l>>LOGS].brute(l&(POWS-1), POWS-1);
		l = (l|(POWS-1))+1;
	}
	if ((r&(POWS-1)) != (POWS-1) && l <= r) {
		ret += nodes[r>>LOGS].brute(0, r&(POWS-1));
		r = (r&(0x7FFFFFFF^(POWS-1)))-1;
	}
	for (; l <= r; l += POWS)
		ret += nodes[l>>LOGS].abval;
	return ret;
}
void inc_val(int l, int r, int x) {
	if (x == 0)
		return ;
	if ((l>>LOGS) == (r>>LOGS)) {
		nodes[l>>LOGS].inc(l&(POWS-1), r&(POWS-1), x);
		return ;
	}
	if (l&(POWS-1)) {
		nodes[l>>LOGS].inc(l&(POWS-1), POWS-1, x);
		l = (l|(POWS-1))+1;
	}
	if ((r&(POWS-1)) != (POWS-1) && l <= r) {
		nodes[r>>LOGS].inc(0, r&(POWS-1), x);
		r = (r&(0x7FFFFFFF^(POWS-1)))-1;
	}
	for (; l <= r; l += POWS)
		nodes[l>>LOGS].inc(0, POWS-1, x);
}
int main() {
	int n, m;
	static int A[MAXN];
	while (scanf("%d%d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		
		for (int i = 0; i < n; i += POWS) {
			int l = i, r = min(l+POWS, n);
			nodes[l>>LOGS].init(l, r, A, buffA+l, buffB+l, buffS+l);
		}
		
		for (int i = 0; i < m; i++) {
			int cmd, l, r, x;
			scanf("%d", &cmd);
			if (cmd == 0) {
				scanf("%d%d", &l, &r);
				printf("%lld\n", sum_abs(l, r));
			} else {
				scanf("%d%d%d", &l, &r, &x);
				inc_val(l, r, x);
			}
		}
	}
	return 0;
}
/*
8 10
0 1 -3 2 -6 1 4 -1
0 2 6
0 1 3
0 3 4
1 2 4 1
0 0 7
0 0 5
1 2 4 4
1 4 5 -5
1 1 7 -5
0 5 5
*/




