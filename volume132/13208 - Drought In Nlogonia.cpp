#include <bits/stdc++.h>
using namespace std;
static const int MAXN = 65536;
static int x[MAXN], h[MAXN];

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
	int testcase;
//	scanf("%d", &testcase);
	M::ReadInt(&testcase);
	while (testcase--) {
		int a, n;
		M::ReadInt(&a);
		M::ReadInt(&n);
//		scanf("%d %d", &a, &n);
		for (int i = 1; i <= n; i++)
//			scanf("%d", &x[i]);
			M::ReadInt(&x[i]);
		for (int i = 0; i <= n; i++)
//			scanf("%d", &h[i]);
			M::ReadInt(&h[i]);
		stack< pair<int, int> > stk;
		stk.push(make_pair(h[0], 0));
		
		int64_t ret = 0;
		for (int i = 1; i <= n; i++) {
			int64_t dist = x[i], mx = 0;
			while (stk.size() && stk.top().first <= h[i]) {
				ret += (stk.top().first-mx) * dist;
				dist += stk.top().second, mx = stk.top().first;
				stk.pop();
			}
			if (stk.size())
				ret += (h[i]-mx) * dist;
			stk.push(make_pair(h[i], dist));
		}
		ret = ret * a;
		printf("%lld\n", ret);
	}
	return 0;
}
/*
1
10  6
10  6  6  8  8  7
20  24  8  18  18  12  15
*/
