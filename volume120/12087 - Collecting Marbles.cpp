#include <bits/stdc++.h>
using namespace std;
const int MAXN = 505;
int g[MAXN][MAXN];
int rg[MAXN][MAXN], cg[MAXN][MAXN];
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
int main() {
	int testcase, cases = 0;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
		int n, m, q;
//		scanf("%d %d %d", &n, &m, &q);
		ReadInt(&n), ReadInt(&m), ReadInt(&q);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
//				scanf("%d", &g[i][j]);
				ReadInt(&g[i][j]);
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1, s = 0; j <= m; j++)
				s += g[i][j], rg[i][j] = s;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				cg[j][i] = cg[j][i-1] + g[i][j];
		}
		
		static int tmp[MAXN];
		printf("Test Case %d:\n", ++cases);
		for (int it = 0; it < q; it++) {
			int lx, ly, rx, ry;
//			scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
			ReadInt(&lx), ReadInt(&ly), ReadInt(&rx), ReadInt(&ry);
			int64_t sl = 0, wl = 0, sr = 0, wr = 0;
			int64_t lmn = LONG_LONG_MAX, rmn = LONG_LONG_MAX;
			for (int i = rx; i >= lx; i--) {
				tmp[i] = rg[i][ry]-rg[i][ly-1];
				sr += tmp[i], wr += sr;
			}
			for (int i = lx; i <= rx; i++) {
				wr -= sr, sr -= tmp[i];
				lmn = min(lmn, wl+wr);
				sl += tmp[i], wl += sl;
			}
			sl = wl = sr = wr = 0;
			for (int i = ry; i >= ly; i--) {
				tmp[i] = cg[i][rx]-cg[i][lx-1];
				sr += tmp[i], wr += sr;
			}
			for (int i = ly; i <= ry; i++) {
				wr -= sr, sr -= tmp[i];
				rmn = min(rmn, wl+wr);
				sl += tmp[i], wl += sl;
			}
			printf("%d %lld\n", it+1, lmn+rmn);
		}
		puts("");
	}
	return 0;
}
/*
2
3 4 3
1 2 3 4
5 6 7 8
9 10 11 12
1 1 3 4
1 1 2 2
1 1 3 3

3 3 3
2 1 3
4 6 1
11 2 3
1 1 3 3
1 1 2 3
2 1 3 3
*/
