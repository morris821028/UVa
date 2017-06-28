#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 512;
static int W[MAXN*MAXN], D[MAXN];

#include <bits/stdc++.h> 
  
namespace M {
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
	int testcase, n;
//	scanf("%d", &testcase);
	M::ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d", &n);
		M::ReadInt(&n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
//				scanf("%d", &W[i*n+j]);
				M::ReadInt(&W[i*n+j]);
		}
		for (int i = 0; i < n; i++)
//			scanf("%d", &D[i]);
			M::ReadInt(&D[i]);
		
		int64_t ret = 0;
		for (int i = n-1; i >= 0; i--) {
			int x = D[i];
			for (int j = 0; j < n; j++) {
				int *W1 = W+j*n, *W2 = W+x*n;
				int b = W[j*n+x];
				for (int k = 0; k < n; k++)
					W1[k] = min(W1[k], b+W2[k]);
			}
			
			int64_t tmp = 0;
			for (int j = i; j < n; j++) {
				int u = D[j];
				int *W1 = W+u*n;
				for (int k = i; k < n; k++) {
					int v = D[k];
					tmp += W1[v];
				}
			}
			ret = ret + tmp;
		}
		
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3
3
0  35  58
12  0  5
1  2  0
0  1  2
3
0  9982  1413
8327  0  5612
3577  7893  0
1  0  2
4
0  50  10  30
4  0  23  58
2  1  0  5
67  24  25  0
0  3  1  2
*/
