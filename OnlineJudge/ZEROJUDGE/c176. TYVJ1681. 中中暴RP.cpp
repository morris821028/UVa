#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define MAXN (1<<17)
#define LOGS 7
#define POWS (1<<LOGS)

long long buffA[MAXN], buffS[MAXN];
int buffP[MAXN];
struct Local {
	Local(long long *A): A(A) {}
	bool operator() (int i, int j) { return A[i] < A[j]; }
	long long *A;
};

struct Node {
	int n, *P;
	long long *A, *S;
	long long val, lazy;
	void init(int l, int r, long long I[], long long *ptrA, long long *ptrS, int *ptrP) {
		A = ptrA, S = ptrS, P = ptrP;
		S[0] = 0, S++;
		n = 0, val = lazy = 0;
		for (int i = l; i < r; i++) {
			P[n] = n, n++;
			if (I[i] > 0)
				val += I[i];
		}
		sort(P, P+n, Local(A));
		for (int i = 0; i < n; i++)
			S[i] = S[i-1] + A[P[i]];
	}
	inline long long range(int l, int r) {
		return S[r] - S[l-1] + lazy * (r-l+1);
	}
	inline int lower_bound(int l, int r, long long v) {
		while (l <= r) {
			int mid = (l + r)>>1;
			if (A[P[mid]] < v)
				l = mid+1;
			else
				r = mid-1;
		}
		return l;
	}
	inline int upper_bound(int l, int r, long long v) {
		while (l <= r) {
			int mid = (l + r)>>1;
			if (A[P[mid]] <= v)
				l = mid+1;
			else
				r = mid-1;
		}
		return l;
	}
	void inc(long long x) {
		if (range(0, 0) >= -x) {
			lazy += x, val = range(0, n-1);
			return ;
		}
		if (range(n-1, n-1) <= -x) {
			lazy += x, val = 0;
			return ;
		}
		if (x > 0) {
			lazy += x;
			int lpos = lower_bound(0, n-1, -lazy);
			val = range(lpos, n-1);
		} else {
			lazy += x;
			int lpos = upper_bound(0, n-1, -lazy);
			val = range(lpos, n-1);
		}
		return ;

	}
	void inc(int l, int r, long long x) {
		val = 0;
		for (int i = 0; i < n; i++) {
			A[i] += lazy;
			if (i >= l && i <= r)
				A[i] += x;
			if (A[i] > 0)
				val += A[i];
		}
		lazy = 0;
		static int PA[POWS], PB[POWS];
		int *endA = PA, *endB = PB, *binA = PA, *binB = PB;
		int idx = 0;
		for (int i = 0; i < n; i++) {
			if (P[i] < l || P[i] > r)
				*endA = P[i], endA++;
			else
				*endB = P[i], endB++;
		}
		while (binA != endA && binB != endB) {
			if (A[*binA] <= A[*binB])
				P[idx++] = *binA, binA++;
			else
				P[idx++] = *binB, binB++;
		}
		memcpy(P+idx, binA, sizeof(P[0])*(endA-binA));
		memcpy(P+idx, binB, sizeof(P[0])*(endB-binB));

		for (int i = 0; i < n; i++)
			S[i] = S[i-1] + A[P[i]];
	}
	inline long long brute(int l, int r) {
		long long ret = 0;
		for (int i = l; i <= r; i++) {
			if (A[i]+lazy > 0)
				ret += A[i]+lazy;
		}
		return ret;
	}
} nodes[MAXN/POWS];
long long sum_abs(int l, int r) {
	if ((l>>LOGS) == (r>>LOGS))
		return nodes[l>>LOGS].brute(l&(POWS-1), r&(POWS-1));
	long long ret = 0;
	if (l&(POWS-1)) {
		ret += nodes[l>>LOGS].brute(l&(POWS-1), POWS-1);
		l = (l|(POWS-1))+1;
	}
	if ((r&(POWS-1)) != (POWS-1) && l <= r) {
		ret += nodes[r>>LOGS].brute(0, r&(POWS-1));
		r = (r&(0x7FFFFFFF^(POWS-1)))-1;
	}
	if (l > r)
		return ret;
	for (l >>= LOGS, r >>= LOGS; l <= r; l++)
		ret += nodes[l].val;
	return ret;
}
void inc_val(int l, int r, long long x) {
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
	if (l > r)
		return ;
	for (l >>= LOGS, r >>= LOGS; l <= r; l++)
		nodes[l].inc(x);
}
namespace MM {
    inline int readchar() {
        const int N = 1048576;
        static char buf[N];
        static char *p = buf, *end = buf;
        if(p == end) {
            if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
            p = buf;
        }
        return *p++;
    }
    inline int ReadInt(int *x) {
        static char c, neg;
        while((c = readchar()) < '-')    {if(c == EOF) return 0;}
        neg = (c == '-') ? -1 : 1;
        *x = (neg == 1) ? c-'0' : 0;
        while((c = readchar()) >= '0')
            *x = (*x << 3) + (*x << 1) + c-'0';
        *x *= neg;
        return 1;
    }
    inline int ReadInt64(long long *x) {
        static char c, neg;
        while((c = readchar()) < '-')    {if(c == EOF) return 0;}
        neg = (c == '-') ? -1 : 1;
        *x = (neg == 1) ? c-'0' : 0;
        while((c = readchar()) >= '0')
            *x = (*x << 3) + (*x << 1) + c-'0';
        *x *= neg;
        return 1;
    }

    class Print {
    public:
        static const int N = 1048576;
        char buf[N], *p, *end;
        Print() {
            p = buf, end = buf + N - 1;
        }
        void printInt(int x, char padding) {
            static char stk[16];
            int idx = 0;
            stk[idx++] = padding;
            if (!x)	
                stk[idx++] = '0';
            while (x)
                stk[idx++] = x%10 + '0', x /= 10;
            while (idx) {
                if (p == end) {
                    *p = '\0';
                    printf("%s", buf), p = buf;
                }
                *p = stk[--idx], p++;
            }
        }
        void printInt64(long long x, char padding) {
            static char stk[24];
            int idx = 0;
			int neg = 0;
            stk[idx++] = padding;
            if (!x)	
                stk[idx++] = '0';
			if (x < 0)
				neg = 1, x = -x;
            while (x)
                stk[idx++] = x%10 + '0', x /= 10;
			if (neg)
				stk[idx++] = '-';
            while (idx) {
                if (p == end) {
                    *p = '\0';
                    printf("%s", buf), p = buf;
                }
                *p = stk[--idx], p++;
            }
        }

        static inline void online_printInt(int x) {
            static char ch[16];
            static int idx;
            idx = 0;
            if (x == 0)	ch[++idx] = 0;
            while (x > 0) ch[++idx] = x % 10, x /= 10;
            while (idx) 
                putchar(ch[idx--]+48);
        }
        ~Print() {
            *p = '\0';
            printf("%s", buf);
        }
    } bprint;
}
int main() {
	int n, m;
//	while (scanf("%d%d", &n, &m) == 2) {
	while (MM::ReadInt(&n)) {
		MM::ReadInt(&m);
		for (int i = 0; i < n; i++)
			MM::ReadInt64(&buffA[i]);

		for (int i = 0, j = 0; i < n; i += POWS, j += POWS+1) {
			int l = i, r = min(l+POWS, n);
			nodes[l>>LOGS].init(l, r, buffA, buffA+l, buffS+j, buffP+l);
		}
		char cmd;
		for (int i = 0; i < m; i++) {
			int l, r;
			long long x;
			while ((cmd = MM::readchar()) <= ' ');
			if (cmd == '+') {
				MM::ReadInt(&l), MM::ReadInt(&r), MM::ReadInt64(&x);
				l--, r--;
				inc_val(l, r, x);
			} else if (cmd == '-') {
				MM::ReadInt(&l), MM::ReadInt(&r), MM::ReadInt64(&x);
				l--, r--;
				inc_val(l, r, -x);
			} else {
				MM::ReadInt(&l), MM::ReadInt(&r);
				l--, r--;
				MM::bprint.printInt64(sum_abs(l, r), '\n');
//				printf("%lld\n", sum_abs(l, r));
			}
		}
	}
	return 0;
}

