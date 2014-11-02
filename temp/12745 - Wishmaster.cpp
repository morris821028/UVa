#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
#define MAXN 262144
vector<int> g[MAXN];
int vfind[MAXN], findIdx;
int stk[MAXN], stkIdx;
int in_stk[MAXN], visited[MAXN];
int contract[MAXN];
int scc_cnt;
int scc(int nd) {
    in_stk[nd] = visited[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd];
    for(int i = 0; i < g[nd].size(); i++) {
        if(!visited[g[nd][i]])
            mn = min(mn, scc(g[nd][i]));
        if(in_stk[g[nd][i]])
            mn = min(mn, vfind[g[nd][i]]);
    }
    if(mn == vfind[nd]) {
        do {
            in_stk[stk[stkIdx]] = 0;
            contract[stk[stkIdx]] = nd;
        } while(stk[stkIdx--] != nd);
        scc_cnt++;
    }
    return mn;
}
int main() {
    int testcase, n, m, cases = 0;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        n = (n + 1)* 2;
        for(int i = 0; i < n; i++)
            g[i].clear();
        // 2*node: false, 2*node+1: true
        while(m--) {
        	int a, b, x, y;
        	scanf("%d %d", &a, &b);
        	x = abs(a), y = abs(b);
        	x <<= 1, y <<= 1;
        	if (a < 0)	x ^= 1;
        	if (b < 0)	y ^= 1;
        	g[x^1].push_back(y);
        	g[y^1].push_back(x);
        }
        //SCC
        memset(visited, 0, sizeof(visited));
        memset(in_stk, 0, sizeof(in_stk));
        scc_cnt = 1;
        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                stkIdx = 0;
                findIdx = 0;
                scc(i);
            }
        }
        //2-SAT check
        int hasSol = 1;
        for(int i = 0; i < n && hasSol; i+=2)
            if(contract[i] == contract[i^1])
                hasSol = 0;
            
        printf("Case %d: %s\n", ++cases, hasSol ? "Yes" : "No");
    }
    return 0;
}
/*
2
3 5
-1 2
1 3
3 -2
1 -3
-2 -3
4 4
-1 2
1 3
-2 4
-3 -4
*/
