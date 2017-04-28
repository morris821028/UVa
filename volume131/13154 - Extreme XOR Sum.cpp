#include <bits/stdc++.h>
using namespace std;

static const int M = (1<<7);
static const int MAXN = 10005;
static int A[M+1][MAXN];
void miniature(int n) {
	for (int i = 1; i*M < n; i++) {
		for (int j = 0; j+i*M < n; j++)
			A[i][j] = A[i-1][j] ^ A[i-1][j+M];
	}
}
int extract(int l, int r) {
	const int n = r-l;
	const int m = n/M;
	const int o = n%M;
	int ret = A[m][l];
	for (int i = o; i; i = (i-1)&o)
		ret ^= A[m][l+i];
	return ret;	
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
        void flush() {
        	*p = '\0', p = buf;
            printf("%s", buf);
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
	int testcase, cases = 0;
	int n, m;
//	scanf("%d", &testcase);
	MM::ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d", &n);
		MM::ReadInt(&n);
		for (int i = 0; i < n; i++)
//			scanf("%d", &A[0][i]);
			MM::ReadInt(&A[0][i]);
		miniature(n);
//		scanf("%d", &m);
		MM::ReadInt(&m);
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < m; i++) {
			int l, r;
//			scanf("%d %d", &l, &r);
			MM::ReadInt(&l), MM::ReadInt(&r);
//			printf("%d\n", extract(l, r));
			MM::bprint.printInt(extract(l, r), '\n');
		}
		MM::bprint.flush();
	}
	return 0;
}
/*
1
5
1  4  6  7  8
3
0  0
0  1
2  4
*/
