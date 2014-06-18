#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
#define maxN 10010
using namespace std;
vector<int> g[maxN];
int stk[maxN], stkIdx;
int visited[maxN], in_stk[maxN];
int vfind[maxN], findIdx;
int lead[maxN];
int scc(int nd) {
    visited[nd] = in_stk[nd] = 1;
    stk[++stkIdx] = nd;
    vfind[nd] = ++findIdx;
    int mn = vfind[nd];
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(!visited[*it]) {
            mn = min(mn, scc(*it));
        }
        if(in_stk[*it]) {
            mn = min(mn, vfind[*it]);
        }
    }
    if(mn == vfind[nd]) {
        do {
            lead[stk[stkIdx]] = nd;
            in_stk[stk[stkIdx]] = 0;
        } while(stk[stkIdx--] != nd);
    }
    return mn;
}
int main() {
    int n, m, t, x, y;
    int i, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 1; i <= n; i++) {
            g[i].clear();
            vfind[i] = visited[i] = in_stk[i] = 0;
            lead[i] = i;
        }
        while(m--) {
            scanf("%d %d", &x, &y);
            g[x].push_back(y);
        }
        for(i = 1; i <= n; i++) {
            if(!visited[i]) {
                findIdx = 0, stkIdx = -1;
                scc(i);
            }
        }
        int indeg[10005] = {};
        for(i = 1; i <= n; i++) {
            for(vector<int>::iterator it = g[i].begin();
                it != g[i].end(); it++) {
                if(lead[*it] != *it)
                    indeg[*it]++;
                if(lead[i] != lead[*it])
                    indeg[lead[*it]]++;
            }
        }
        int ans = 0;
        for(i = 1; i <= n; i++)
            if(!indeg[i] && lead[i] == i)
                ans++;
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
