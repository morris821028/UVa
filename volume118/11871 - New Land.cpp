#include <stdio.h>
#include <stack>
#include <algorithm>
using namespace std;
// http://mypaper.pchome.com.tw/zerojudge/post/1326159411
int solve(int n, int h[]) {
    int ret = 0;
    int i, height;
    stack< pair<int, int> > stk;// <height, position>
    pair<int, int> e;
    stk.push(make_pair(-1, 0));
    h[n] = 0;// visual height.
    for(i = 0; i <= n; i++) {
        height = h[i];
        e = make_pair(height, i);
        while(height < stk.top().first) {
            e = stk.top(), stk.pop();
            ret = max(ret, (i - e.second) * e.first);
        }
        if(height > stk.top().first)
            stk.push(make_pair(height, e.second));
    }
    return ret;
}    
int n, m, h[2048];
short g[2048][2048];
int main() {
	int k, c, x, cases = 0;
	scanf("%*d");
    while(scanf("%d %d", &n, &m) == 2) {
        for(int i = 0; i < n; i++) {
        	scanf("%d %d", &k, &c);
        	int pos = 0;
            for(int j = 0; j < k; j++) {
            	scanf("%d", &x);
				c = !c;
            	while(x--)
            		g[i][pos++] = c;            	
            }
        }
        for(int i = 0; i < n; i++) {
            int sum = 0;
            for(int j = 0; j < m; j++) {
                sum += g[i][j];
                if(g[i][j] == 0)    
                    sum = 0;
                g[i][j] = sum;
            }
        }
        int ret = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++)
                h[j] = g[j][i];
            for(int j = 0; j < n; j++)
            	printf("%d", h[j]);
            puts("");
            ret = max(ret, solve(n, h));
        }
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
} 
