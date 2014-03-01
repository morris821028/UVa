#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
unsigned short dp1[200000][2], dp2[200000];
vector<int> g[200000];
void dfs1(int nd, int p) {
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(*it != p) {
            dfs1(*it, nd);
            if(dp1[*it][0]+1 > dp1[nd][1])
                dp1[nd][1] = dp1[*it][0]+1;
            if(dp1[nd][0] < dp1[nd][1])
                swap(dp1[nd][0], dp1[nd][1]);
        }
    }
}
void dfs2(int nd, int p) {
    if(nd) {
        if(dp1[nd][0]+1 == dp1[p][0])
            dp2[nd] = max(dp1[p][1], dp2[p])+1;
        else
            dp2[nd] = max(dp1[p][0], dp2[p])+1;
    }
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(*it != p)
            dfs2(*it, nd);
    }
}
int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, i, x, y;
    scanf("%d", &n);
    for(i = 1; i < n; i++) {
        ReadInt(&x);
        ReadInt(&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs1(0, -1);
    dfs2(0, -1);
    int longest = 0;
    for(i = 0; i < n; i++) {
        longest = max(longest, dp1[i][0]+dp1[i][1]);
        longest = max(longest, dp1[i][0]+dp2[i]);
    }
    for(i = 0; i < n; i++) {
        if(longest == dp1[i][0]+dp1[i][1] ||
           longest == dp1[i][0]+dp2[i]) {
            printf("%d\n", i);
        }
    }
    return 0;
}
