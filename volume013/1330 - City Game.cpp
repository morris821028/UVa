#include <stdio.h>
#include <stack>
#include <algorithm>
#include <string.h>
#define MAXL ((1024*1024)>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
using namespace std;
int mark[MAXL];
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
    int k, c, x, cases = 0, testcase;
//    ReadInt(&testcase);
	scanf("%d", &testcase);
    while(testcase--) {
//    	ReadInt(&n);
//    	ReadInt(&m);
    	scanf("%d %d", &n, &m);
    	memset(mark, 0, sizeof(mark));
    	memset(h, 0, sizeof(h));
    	for (int i = 0; i < n; i++) {
    		char cmd[8];
    		for (int j = 0; j < m; j++) {
    			scanf("%s", cmd);
    			if (cmd[0] == 'F')
    				SET(i*1024+j);
			}
		}
        int ret = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
            	if(GET(j*1024 + i))
            		h[j]++;
            	else
            		h[j] = 0;
            }
            ret = max(ret, solve(n, h));
        }
        printf("%d\n", ret*3);
    }
    return 0;
} 
/*
2
5 6
R F F F F F
F F F F F F
R R R F F F
F F F F F F
F F F F F F

5 5
R R R R R
R R R R R 
R R R R R
R R R R R
R R R R R
*/
