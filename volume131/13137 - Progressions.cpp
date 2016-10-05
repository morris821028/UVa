#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1024;
int A[MAXN][MAXN];
int th[MAXN][MAXN];
int solve(int id, int n, int h[]) {
    int ret = 0;
    int i, height;
    stack< pair<int, int> > stk;// <height, position>
    pair<int, int> e;
    stk.push(make_pair(-1, 1));
    h[n+1] = 0;// visual height.
    for (i = 1; i <= n+1; i++) {
        height = h[i];
//        printf("- %d\n", h[i]);
        e = make_pair(height, i);
        if (i <= n && i > 1 && A[i][id] != A[i-1][id]+1) {
        	while (stk.size() > 1) {
        		e = stk.top(), stk.pop();
//        		printf("? %d %d\n", i-e.second, e.first);
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
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &A[i][j]);
				th[i][j] = A[i][j] == A[i][j-1]+1;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (th[i][j] && j != 1)	
					th[i][j] = th[i][j-1]+1;
				else
					th[i][j] = 1;
			}
		}
		
		int ret = 0;
		for (int j = 1; j <= m; j++) {
			int h[MAXN];
			for (int i = 1; i <= n; i++)
				h[i] = th[i][j];
			int t = solve(j, n, h);
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

