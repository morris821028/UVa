#include <stdio.h>
#include <vector>
#include <stack>
#include <algorithm>
#define maxN 2010
using namespace std;
vector<int> g[maxN];
int stk[maxN], stkIdx;
int visited[maxN], in_stk[maxN];
int vfind[maxN], findIdx;
int scc_cnt;
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
        scc_cnt++;
        do {
            in_stk[stk[stkIdx]] = 0;
        } while(stk[stkIdx--] != nd);
    }
    return mn;
}
int main() {
    int n, m, x, y, c;
    int i;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        for(i = 1; i <= n; i++) {
            g[i].clear();
            vfind[i] = visited[i] = in_stk[i] = 0;
        }
        while(m--) {
            scanf("%d %d %d", &x, &y, &c);
            g[x].push_back(y);
            if(c == 2)
                g[y].push_back(x);
        }
        scc_cnt = 0;
        for(i = 1; i <= n; i++) {
            if(!visited[i] && scc_cnt <= 1) {
                findIdx = 0, stkIdx = -1;
                scc(i);
            }
        }
        if(scc_cnt == 1)
            puts("1");
        else
            puts("0");
    }
    return 0;
}
