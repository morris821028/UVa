#include <stdio.h>
#include <stack>
#include <algorithm>
#include <string.h>
#define maxL ((2048*2048)>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
using namespace std;
int mark[maxL];
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
int main() {
	int k, c, x, cases = 0;
	scanf("%*d");
    while(scanf("%d %d", &n, &m) == 2) {
    	memset(mark, 0, sizeof(mark));
    	memset(h, 0, sizeof(h));
        for(int i = 0; i < n; i++) {
        	scanf("%d %d", &k, &c);
        	int pos = 0;
            for(int j = 0; j < k; j++) {
            	scanf("%d", &x);
				c = !c;
				if(c) {
            		while(x--)
            			SET(i * 2048 + pos), pos++;
            	} else {
            		pos += x;
            	}
            }
        }
        int ret = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
            	if(GET(j * 2048 + i))
            		h[j]++;
            	else
            		h[j] = 0;
            }
            ret = max(ret, solve(n, h));
        }
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
} 
