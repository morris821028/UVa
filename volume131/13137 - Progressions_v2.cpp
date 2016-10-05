#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1024;
int A[MAXN][MAXN];
short th[MAXN][MAXN];
int solve(int id, int n, int h[]) {
    int ret = 0;
    int i, height;
    stack< pair<int, int> > stk;// <height, position>
    pair<int, int> e;
    stk.push(make_pair(-1, 1));
    h[n+1] = 0;// visual height.
    for (i = 1; i <= n+1; i++) {
        height = h[i];
        e = make_pair(height, i);
        if (i <= n && i > 1 && A[id][i] != A[id][i-1]+1) {
        	while (stk.size() > 1) {
        		e = stk.top(), stk.pop();
        		ret = max(ret, (i - e.second) * e.first);
			}
			e.second = i;
		}
        while (height < stk.top().first) {
            e = stk.top(), stk.pop();
            ret = max(ret, (i - e.second) * e.first);
        }
        if (height > stk.top().first)
            stk.push(make_pair(height, e.second));
    }
    return ret;
}
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
	int n, m;
//	while (scanf("%d %d", &n, &m) == 2) {
	while (ReadInt(&n)) {
	 	ReadInt(&m);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
//				scanf("%d", &A[i][j]);
				ReadInt(&A[i][j]);
				th[i][j] = A[i][j] == A[i-1][j]+1;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (th[i][j] && i != 1)	
					th[i][j] = th[i-1][j]+1;
				else
					th[i][j] = 1;
			}
		}
		
		int ret = 0;
		for (int i = 1; i <= n; i++) {
			int h[MAXN];
			for (int j = 1; j <= m; j++)
				h[j] = th[i][j];
			int t = solve(i, m, h);
			ret = max(ret, t);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
4  7
3  4  5  6  7  8  9
5  4  2  7  8  9  10
6  3  1  8  9  11  11
7  4  2  9  11  10  12
2 2
4 4
4 4
1 5
1 2 3 4 5
*/

